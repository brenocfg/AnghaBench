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
struct mtk_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFI_STA ; 
 int STA_BUSY ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int nfi_readl (struct mtk_nfc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_nfc_dev_ready(struct nand_chip *nand)
{
	struct mtk_nfc *nfc = nand_get_controller_data(nand);

	if (nfi_readl(nfc, NFI_STA) & STA_BUSY)
		return 0;

	return 1;
}