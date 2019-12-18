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
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  sector_size_1k; } ;
struct brcmnand_host {TYPE_1__ hwcfg; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {unsigned int max_oob; int /*<<< orphan*/  dev; int /*<<< orphan*/  soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PROGRAM_PAGE ; 
 int EIO ; 
 scalar_t__ FC_BYTES ; 
 unsigned int FC_SHIFT ; 
 unsigned int FC_WORDS ; 
 int NAND_STATUS_FAIL ; 
 scalar_t__ brcmnand_dma_trans (struct brcmnand_host*,scalar_t__,int*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_send_cmd (struct brcmnand_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_set_cmd_addr (struct mtd_info*,scalar_t__) ; 
 int /*<<< orphan*/  brcmnand_soc_data_bus_prepare (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmnand_soc_data_bus_unprepare (int /*<<< orphan*/ ,int) ; 
 int brcmnand_waitfunc (struct nand_chip*) ; 
 int /*<<< orphan*/  brcmnand_wp (struct mtd_info*,int) ; 
 int /*<<< orphan*/  brcmnand_write_fc (struct brcmnand_controller*,unsigned int,int const) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long long,int const*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int const*) ; 
 scalar_t__ flash_dma_buf_ok (int const*) ; 
 scalar_t__ has_flash_dma (struct brcmnand_controller*) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  oob_reg_write (struct brcmnand_controller*,unsigned int,int) ; 
 scalar_t__ unlikely (unsigned long) ; 
 int /*<<< orphan*/  write_oob_to_regs (struct brcmnand_controller*,unsigned int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmnand_write(struct mtd_info *mtd, struct nand_chip *chip,
			  u64 addr, const u32 *buf, u8 *oob)
{
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;
	unsigned int i, j, trans = mtd->writesize >> FC_SHIFT;
	int status, ret = 0;

	dev_dbg(ctrl->dev, "write %llx <- %p\n", (unsigned long long)addr, buf);

	if (unlikely((unsigned long)buf & 0x03)) {
		dev_warn(ctrl->dev, "unaligned buffer: %p\n", buf);
		buf = (u32 *)((unsigned long)buf & ~0x03);
	}

	brcmnand_wp(mtd, 0);

	for (i = 0; i < ctrl->max_oob; i += 4)
		oob_reg_write(ctrl, i, 0xffffffff);

	if (has_flash_dma(ctrl) && !oob && flash_dma_buf_ok(buf)) {
		if (brcmnand_dma_trans(host, addr, (u32 *)buf,
					mtd->writesize, CMD_PROGRAM_PAGE))
			ret = -EIO;
		goto out;
	}

	for (i = 0; i < trans; i++, addr += FC_BYTES) {
		/* full address MUST be set before populating FC */
		brcmnand_set_cmd_addr(mtd, addr);

		if (buf) {
			brcmnand_soc_data_bus_prepare(ctrl->soc, false);

			for (j = 0; j < FC_WORDS; j++, buf++)
				brcmnand_write_fc(ctrl, j, *buf);

			brcmnand_soc_data_bus_unprepare(ctrl->soc, false);
		} else if (oob) {
			for (j = 0; j < FC_WORDS; j++)
				brcmnand_write_fc(ctrl, j, 0xffffffff);
		}

		if (oob) {
			oob += write_oob_to_regs(ctrl, i, oob,
					mtd->oobsize / trans,
					host->hwcfg.sector_size_1k);
		}

		/* we cannot use SPARE_AREA_PROGRAM when PARTIAL_PAGE_EN=0 */
		brcmnand_send_cmd(host, CMD_PROGRAM_PAGE);
		status = brcmnand_waitfunc(chip);

		if (status & NAND_STATUS_FAIL) {
			dev_info(ctrl->dev, "program failed at %llx\n",
				(unsigned long long)addr);
			ret = -EIO;
			goto out;
		}
	}
out:
	brcmnand_wp(mtd, 1);
	return ret;
}