#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct nand_chip {int dummy; } ;
struct mxc_nand_host {int active_cs; int /*<<< orphan*/  main_area0; TYPE_1__* devtype_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  failed; int /*<<< orphan*/  corrected; } ;
struct mtd_info {int writesize; TYPE_2__ ecc_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* send_cmd ) (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* enable_hwecc ) (struct nand_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int /*<<< orphan*/  NAND_CMD_READSTART ; 
 int NFC_OUTPUT ; 
 int /*<<< orphan*/  NFC_V1_V2_BUF_ADDR ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG2 ; 
 int /*<<< orphan*/  copy_spare (struct mtd_info*,int,void*) ; 
 int get_ecc_status_v1 (struct mxc_nand_host*) ; 
 int /*<<< orphan*/  memcpy32_fromio (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_do_addr_cycle (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int) ; 
 int /*<<< orphan*/  stub2 (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc_nand_read_page_v1(struct nand_chip *chip, void *buf, void *oob,
				 bool ecc, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mxc_nand_host *host = nand_get_controller_data(chip);
	unsigned int bitflips_corrected = 0;
	int no_subpages;
	int i;

	host->devtype_data->enable_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, NAND_CMD_READ0, false);
	mxc_do_addr_cycle(mtd, 0, page);

	if (mtd->writesize > 512)
		host->devtype_data->send_cmd(host, NAND_CMD_READSTART, true);

	no_subpages = mtd->writesize >> 9;

	for (i = 0; i < no_subpages; i++) {
		uint16_t ecc_stats;

		/* NANDFC buffer 0 is used for page read/write */
		writew((host->active_cs << 4) | i, NFC_V1_V2_BUF_ADDR);

		writew(NFC_OUTPUT, NFC_V1_V2_CONFIG2);

		/* Wait for operation to complete */
		wait_op_done(host, true);

		ecc_stats = get_ecc_status_v1(host);

		ecc_stats >>= 2;

		if (buf && ecc) {
			switch (ecc_stats & 0x3) {
			case 0:
			default:
				break;
			case 1:
				mtd->ecc_stats.corrected++;
				bitflips_corrected = 1;
				break;
			case 2:
				mtd->ecc_stats.failed++;
				break;
			}
		}
	}

	if (buf)
		memcpy32_fromio(buf, host->main_area0, mtd->writesize);
	if (oob)
		copy_spare(mtd, true, oob);

	return bitflips_corrected;
}