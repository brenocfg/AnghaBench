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
struct memcard {int partitions; struct memcard* mtd; struct memcard* parts; struct memcard* name; struct mdev_part* priv; } ;
struct mdev_part {int /*<<< orphan*/ * mdev; } ;
struct maple_device {int /*<<< orphan*/ * callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct memcard*) ; 
 struct memcard* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  mtd_device_unregister (struct memcard*) ; 

__attribute__((used)) static void vmu_disconnect(struct maple_device *mdev)
{
	struct memcard *card;
	struct mdev_part *mpart;
	int x;

	mdev->callback = NULL;
	card = maple_get_drvdata(mdev);
	for (x = 0; x < card->partitions; x++) {
		mpart = ((card->mtd)[x]).priv;
		mpart->mdev = NULL;
		mtd_device_unregister(&((card->mtd)[x]));
		kfree(((card->parts)[x]).name);
	}
	kfree(card->parts);
	kfree(card->mtd);
	kfree(card);
}