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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtk_nfc_fdm {int reg_size; } ;
struct mtk_nfc_nand_chip {struct mtk_nfc_fdm fdm; } ;
struct mtk_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFI_FDML (int) ; 
 int /*<<< orphan*/  NFI_FDMM (int) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nfi_writel (struct mtk_nfc*,int,int /*<<< orphan*/ ) ; 
 int* oob_ptr (struct nand_chip*,int) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static inline void mtk_nfc_write_fdm(struct nand_chip *chip)
{
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	struct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 vall, valm;
	u8 *oobptr;
	int i, j;

	for (i = 0; i < chip->ecc.steps; i++) {
		oobptr = oob_ptr(chip, i);
		vall = 0;
		valm = 0;
		for (j = 0; j < 8; j++) {
			if (j < 4)
				vall |= (j < fdm->reg_size ? oobptr[j] : 0xff)
						<< (j * 8);
			else
				valm |= (j < fdm->reg_size ? oobptr[j] : 0xff)
						<< ((j - 4) * 8);
		}
		nfi_writel(nfc, vall, NFI_FDML(i));
		nfi_writel(nfc, valm, NFI_FDMM(i));
	}
}