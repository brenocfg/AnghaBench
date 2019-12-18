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
struct TYPE_2__ {int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct meson_nfc_nand_chip {void* data_buf; void* info_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PER_INFO_BYTE ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct meson_nfc_nand_chip* to_meson_nand (struct nand_chip*) ; 

__attribute__((used)) static int meson_chip_buffer_init(struct nand_chip *nand)
{
	struct mtd_info *mtd = nand_to_mtd(nand);
	struct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u32 page_bytes, info_bytes, nsectors;

	nsectors = mtd->writesize / nand->ecc.size;

	page_bytes =  mtd->writesize + mtd->oobsize;
	info_bytes = nsectors * PER_INFO_BYTE;

	meson_chip->data_buf = kmalloc(page_bytes, GFP_KERNEL);
	if (!meson_chip->data_buf)
		return -ENOMEM;

	meson_chip->info_buf = kmalloc(info_bytes, GFP_KERNEL);
	if (!meson_chip->info_buf) {
		kfree(meson_chip->data_buf);
		return -ENOMEM;
	}

	return 0;
}