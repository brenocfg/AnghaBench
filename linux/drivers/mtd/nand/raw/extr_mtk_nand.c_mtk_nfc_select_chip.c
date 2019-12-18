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
struct nand_chip {int dummy; } ;
struct mtk_nfc_nand_chip {int /*<<< orphan*/ * sels; } ;
struct mtk_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFI_CSEL ; 
 int /*<<< orphan*/  mtk_nfc_hw_runtime_config (int /*<<< orphan*/ ) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  nfi_writel (struct mtk_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static void mtk_nfc_select_chip(struct nand_chip *nand, int chip)
{
	struct mtk_nfc *nfc = nand_get_controller_data(nand);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(nand);

	if (chip < 0)
		return;

	mtk_nfc_hw_runtime_config(nand_to_mtd(nand));

	nfi_writel(nfc, mtk_nand->sels[chip], NFI_CSEL);
}