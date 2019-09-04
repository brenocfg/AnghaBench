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
struct mtd_info {scalar_t__ usecount; } ;
struct memcard {int partitions; struct mtd_info* mtd; } ;
struct maple_device {int dummy; } ;

/* Variables and functions */
 struct memcard* maple_get_drvdata (struct maple_device*) ; 

__attribute__((used)) static int vmu_can_unload(struct maple_device *mdev)
{
	struct memcard *card;
	int x;
	struct mtd_info *mtd;

	card = maple_get_drvdata(mdev);
	for (x = 0; x < card->partitions; x++) {
		mtd = &((card->mtd)[x]);
		if (mtd->usecount > 0)
			return 0;
	}
	return 1;
}