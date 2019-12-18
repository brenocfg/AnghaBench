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
typedef  int u32 ;
struct TYPE_2__ {int steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct meson_nfc_nand_chip {int* info_buf; } ;
struct meson_nfc {int dummy; } ;
typedef  int __le64 ;

/* Variables and functions */
 int ECC_COMPLETE ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct meson_nfc_nand_chip* to_meson_nand (struct nand_chip*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void meson_nfc_check_ecc_pages_valid(struct meson_nfc *nfc,
					    struct nand_chip *nand, int raw)
{
	struct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__le64 *info;
	u32 neccpages;
	int ret;

	neccpages = raw ? 1 : nand->ecc.steps;
	info = &meson_chip->info_buf[neccpages - 1];
	do {
		usleep_range(10, 15);
		/* info is updated by nfc dma engine*/
		smp_rmb();
		ret = *info & ECC_COMPLETE;
	} while (!ret);
}