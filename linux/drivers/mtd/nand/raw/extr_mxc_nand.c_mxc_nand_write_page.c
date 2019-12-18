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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mxc_nand_host {TYPE_1__* devtype_data; int /*<<< orphan*/  main_area0; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_cmd ) (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* send_page ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable_hwecc ) (struct nand_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  NAND_CMD_SEQIN ; 
 int /*<<< orphan*/  NFC_INPUT ; 
 int /*<<< orphan*/  copy_spare (struct mtd_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy32_toio (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_do_addr_cycle (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int) ; 
 int /*<<< orphan*/  stub2 (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxc_nand_write_page(struct nand_chip *chip, const uint8_t *buf,
			       bool ecc, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mxc_nand_host *host = nand_get_controller_data(chip);

	host->devtype_data->enable_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, NAND_CMD_SEQIN, false);
	mxc_do_addr_cycle(mtd, 0, page);

	memcpy32_toio(host->main_area0, buf, mtd->writesize);
	copy_spare(mtd, false, chip->oob_poi);

	host->devtype_data->send_page(mtd, NFC_INPUT);
	host->devtype_data->send_cmd(host, NAND_CMD_PAGEPROG, true);
	mxc_do_addr_cycle(mtd, 0, page);

	return 0;
}