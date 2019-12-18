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
struct mtd_info {struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct flchip {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wq; } ;
struct cfi_private {int numchips; struct flchip* chips; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 scalar_t__ FL_PM_SUSPENDED ; 
 scalar_t__ FL_READY ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfi_staa_resume(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	int i;
	struct flchip *chip;

	for (i=0; i<cfi->numchips; i++) {

		chip = &cfi->chips[i];

		mutex_lock(&chip->mutex);

		/* Go to known state. Chip may have been power cycled */
		if (chip->state == FL_PM_SUSPENDED) {
			map_write(map, CMD(0xFF), 0);
			chip->state = FL_READY;
			wake_up(&chip->wq);
		}

		mutex_unlock(&chip->mutex);
	}
}