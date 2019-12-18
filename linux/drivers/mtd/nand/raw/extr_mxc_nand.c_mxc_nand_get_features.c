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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_byte ) (struct nand_chip*) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;
struct mxc_nand_host {scalar_t__ buf_start; int /*<<< orphan*/  main_area0; int /*<<< orphan*/  data_buf; TYPE_2__* devtype_data; } ;
struct mtd_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_page ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_cmd ) (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_GET_FEATURES ; 
 int /*<<< orphan*/  NFC_OUTPUT ; 
 int ONFI_SUBFEATURE_PARAM_LEN ; 
 int /*<<< orphan*/  memcpy32_fromio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_do_addr_cycle (struct mtd_info*,int,int) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mxc_nand_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct nand_chip*) ; 

__attribute__((used)) static int mxc_nand_get_features(struct nand_chip *chip, int addr,
				 u8 *subfeature_param)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mxc_nand_host *host = nand_get_controller_data(chip);
	int i;

	host->devtype_data->send_cmd(host, NAND_CMD_GET_FEATURES, false);
	mxc_do_addr_cycle(mtd, addr, -1);
	host->devtype_data->send_page(mtd, NFC_OUTPUT);
	memcpy32_fromio(host->data_buf, host->main_area0, 512);
	host->buf_start = 0;

	for (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		*subfeature_param++ = chip->legacy.read_byte(chip);

	return 0;
}