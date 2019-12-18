#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int dummy; } ;
struct TYPE_2__ {unsigned int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {int /*<<< orphan*/  bitflip_threshold; TYPE_1__ ecc_stats; int /*<<< orphan*/  oobsize; } ;
struct brcmnand_host {struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int nand_version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PAGE_READ ; 
 int EIO ; 
 unsigned int FC_BYTES ; 
 int /*<<< orphan*/  brcmnand_clear_ecc_addr (struct brcmnand_controller*) ; 
 unsigned int brcmnand_count_corrected (struct brcmnand_controller*) ; 
 int brcmnand_dma_trans (struct brcmnand_host*,scalar_t__,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int brcmnand_read_by_pio (struct mtd_info*,struct nand_chip*,scalar_t__,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int brcmstb_nand_verify_erased_page (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 scalar_t__ flash_dma_buf_ok (int /*<<< orphan*/ *) ; 
 scalar_t__ has_flash_dma (struct brcmnand_controller*) ; 
 int max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 scalar_t__ mtd_is_bitflip_or_eccerr (int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int brcmnand_read(struct mtd_info *mtd, struct nand_chip *chip,
			 u64 addr, unsigned int trans, u32 *buf, u8 *oob)
{
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;
	u64 err_addr = 0;
	int err;
	bool retry = true;

	dev_dbg(ctrl->dev, "read %llx -> %p\n", (unsigned long long)addr, buf);

try_dmaread:
	brcmnand_clear_ecc_addr(ctrl);

	if (has_flash_dma(ctrl) && !oob && flash_dma_buf_ok(buf)) {
		err = brcmnand_dma_trans(host, addr, buf, trans * FC_BYTES,
					     CMD_PAGE_READ);
		if (err) {
			if (mtd_is_bitflip_or_eccerr(err))
				err_addr = addr;
			else
				return -EIO;
		}
	} else {
		if (oob)
			memset(oob, 0x99, mtd->oobsize);

		err = brcmnand_read_by_pio(mtd, chip, addr, trans, buf,
					       oob, &err_addr);
	}

	if (mtd_is_eccerr(err)) {
		/*
		 * On controller version and 7.0, 7.1 , DMA read after a
		 * prior PIO read that reported uncorrectable error,
		 * the DMA engine captures this error following DMA read
		 * cleared only on subsequent DMA read, so just retry once
		 * to clear a possible false error reported for current DMA
		 * read
		 */
		if ((ctrl->nand_version == 0x0700) ||
		    (ctrl->nand_version == 0x0701)) {
			if (retry) {
				retry = false;
				goto try_dmaread;
			}
		}

		/*
		 * Controller version 7.2 has hw encoder to detect erased page
		 * bitflips, apply sw verification for older controllers only
		 */
		if (ctrl->nand_version < 0x0702) {
			err = brcmstb_nand_verify_erased_page(mtd, chip, buf,
							      addr);
			/* erased page bitflips corrected */
			if (err >= 0)
				return err;
		}

		dev_dbg(ctrl->dev, "uncorrectable error at 0x%llx\n",
			(unsigned long long)err_addr);
		mtd->ecc_stats.failed++;
		/* NAND layer expects zero on ECC errors */
		return 0;
	}

	if (mtd_is_bitflip(err)) {
		unsigned int corrected = brcmnand_count_corrected(ctrl);

		dev_dbg(ctrl->dev, "corrected error at 0x%llx\n",
			(unsigned long long)err_addr);
		mtd->ecc_stats.corrected += corrected;
		/* Always exceed the software-imposed threshold */
		return max(mtd->bitflip_threshold, corrected);
	}

	return 0;
}