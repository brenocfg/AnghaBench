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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int size; } ;
struct nand_chip {TYPE_2__ ecc; } ;
struct mtk_nfc {TYPE_1__* caps; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct TYPE_3__ {int* spare_size; int num_spare_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int MTK_NFC_MIN_SPARE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_set_spare_per_sector(u32 *sps, struct mtd_info *mtd)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mtk_nfc *nfc = nand_get_controller_data(nand);
	const u8 *spare = nfc->caps->spare_size;
	u32 eccsteps, i, closest_spare = 0;

	eccsteps = mtd->writesize / nand->ecc.size;
	*sps = mtd->oobsize / eccsteps;

	if (nand->ecc.size == 1024)
		*sps >>= 1;

	if (*sps < MTK_NFC_MIN_SPARE)
		return -EINVAL;

	for (i = 0; i < nfc->caps->num_spare_size; i++) {
		if (*sps >= spare[i] && spare[i] >= spare[closest_spare]) {
			closest_spare = i;
			if (*sps == spare[i])
				break;
		}
	}

	*sps = spare[closest_spare];

	if (nand->ecc.size == 1024)
		*sps <<= 1;

	return 0;
}