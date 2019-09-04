#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtk_nfc {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNFG_OP_CUST ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int /*<<< orphan*/  NFI_CNFG ; 
 int /*<<< orphan*/  mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  mtk_nfc_hw_reset (struct mtk_nfc*) ; 
 int /*<<< orphan*/  mtk_nfc_send_address (struct mtk_nfc*,int) ; 
 int /*<<< orphan*/  mtk_nfc_send_command (struct mtk_nfc*,int) ; 
 struct mtk_nfc* nand_get_controller_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfi_writew (struct mtk_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_nfc_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
	struct mtk_nfc *nfc = nand_get_controller_data(mtd_to_nand(mtd));

	if (ctrl & NAND_ALE) {
		mtk_nfc_send_address(nfc, dat);
	} else if (ctrl & NAND_CLE) {
		mtk_nfc_hw_reset(nfc);

		nfi_writew(nfc, CNFG_OP_CUST, NFI_CNFG);
		mtk_nfc_send_command(nfc, dat);
	}
}