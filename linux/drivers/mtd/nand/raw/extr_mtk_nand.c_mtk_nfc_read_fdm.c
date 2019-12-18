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
typedef  int u8 ;
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct mtk_nfc_fdm {int reg_size; } ;
struct mtk_nfc_nand_chip {struct mtk_nfc_fdm fdm; } ;
struct mtk_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFI_FDML (int) ; 
 int /*<<< orphan*/  NFI_FDMM (int) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int nfi_readl (struct mtk_nfc*,int /*<<< orphan*/ ) ; 
 int* oob_ptr (struct nand_chip*,int) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static inline void mtk_nfc_read_fdm(struct nand_chip *chip, u32 start,
				    u32 sectors)
{
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	struct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 vall, valm;
	u8 *oobptr;
	int i, j;

	for (i = 0; i < sectors; i++) {
		oobptr = oob_ptr(chip, start + i);
		vall = nfi_readl(nfc, NFI_FDML(i));
		valm = nfi_readl(nfc, NFI_FDMM(i));

		for (j = 0; j < fdm->reg_size; j++)
			oobptr[j] = (j >= 4 ? valm : vall) >> ((j % 4) * 8);
	}
}