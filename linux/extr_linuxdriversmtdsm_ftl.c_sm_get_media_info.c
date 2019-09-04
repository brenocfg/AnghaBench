#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sm_ftl {int readonly; int zone_count; int smallpagenand; int zone_size; int max_lba; int block_size; int cylinders; int heads; int sectors; } ;
struct mtd_info {int size; scalar_t__ type; int writesize; int erasesize; scalar_t__ oobsize; } ;
struct TYPE_3__ {int size; int cyl; int head; int sec; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 scalar_t__ MTD_ROM ; 
 scalar_t__ SM_OOB_SIZE ; 
 int SM_SECTOR_SIZE ; 
 scalar_t__ SM_SMALL_OOB_SIZE ; 
 int SM_SMALL_PAGE ; 
 TYPE_1__* chs_table ; 
 int /*<<< orphan*/  mtd_has_oob (struct mtd_info*) ; 
 int /*<<< orphan*/  sm_printk (char*,int) ; 

__attribute__((used)) static int sm_get_media_info(struct sm_ftl *ftl, struct mtd_info *mtd)
{
	int i;
	int size_in_megs = mtd->size / (1024 * 1024);

	ftl->readonly = mtd->type == MTD_ROM;

	/* Manual settings for very old devices */
	ftl->zone_count = 1;
	ftl->smallpagenand = 0;

	switch (size_in_megs) {
	case 1:
		/* 1 MiB flash/rom SmartMedia card (256 byte pages)*/
		ftl->zone_size = 256;
		ftl->max_lba = 250;
		ftl->block_size = 8 * SM_SECTOR_SIZE;
		ftl->smallpagenand = 1;

		break;
	case 2:
		/* 2 MiB flash SmartMedia (256 byte pages)*/
		if (mtd->writesize == SM_SMALL_PAGE) {
			ftl->zone_size = 512;
			ftl->max_lba = 500;
			ftl->block_size = 8 * SM_SECTOR_SIZE;
			ftl->smallpagenand = 1;
		/* 2 MiB rom SmartMedia */
		} else {

			if (!ftl->readonly)
				return -ENODEV;

			ftl->zone_size = 256;
			ftl->max_lba = 250;
			ftl->block_size = 16 * SM_SECTOR_SIZE;
		}
		break;
	case 4:
		/* 4 MiB flash/rom SmartMedia device */
		ftl->zone_size = 512;
		ftl->max_lba = 500;
		ftl->block_size = 16 * SM_SECTOR_SIZE;
		break;
	case 8:
		/* 8 MiB flash/rom SmartMedia device */
		ftl->zone_size = 1024;
		ftl->max_lba = 1000;
		ftl->block_size = 16 * SM_SECTOR_SIZE;
	}

	/* Minimum xD size is 16MiB. Also, all xD cards have standard zone
	   sizes. SmartMedia cards exist up to 128 MiB and have same layout*/
	if (size_in_megs >= 16) {
		ftl->zone_count = size_in_megs / 16;
		ftl->zone_size = 1024;
		ftl->max_lba = 1000;
		ftl->block_size = 32 * SM_SECTOR_SIZE;
	}

	/* Test for proper write,erase and oob sizes */
	if (mtd->erasesize > ftl->block_size)
		return -ENODEV;

	if (mtd->writesize > SM_SECTOR_SIZE)
		return -ENODEV;

	if (ftl->smallpagenand && mtd->oobsize < SM_SMALL_OOB_SIZE)
		return -ENODEV;

	if (!ftl->smallpagenand && mtd->oobsize < SM_OOB_SIZE)
		return -ENODEV;

	/* We use OOB */
	if (!mtd_has_oob(mtd))
		return -ENODEV;

	/* Find geometry information */
	for (i = 0 ; i < ARRAY_SIZE(chs_table) ; i++) {
		if (chs_table[i].size == size_in_megs) {
			ftl->cylinders = chs_table[i].cyl;
			ftl->heads = chs_table[i].head;
			ftl->sectors = chs_table[i].sec;
			return 0;
		}
	}

	sm_printk("media has unknown size : %dMiB", size_in_megs);
	ftl->cylinders = 985;
	ftl->heads =  33;
	ftl->sectors = 63;
	return 0;
}