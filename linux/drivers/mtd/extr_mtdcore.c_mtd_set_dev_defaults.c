#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* parent; } ;
struct mtd_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  orig_flags; TYPE_1__ dev; scalar_t__ name; scalar_t__ owner; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {scalar_t__ owner; } ;

/* Variables and functions */
 scalar_t__ dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void mtd_set_dev_defaults(struct mtd_info *mtd)
{
	if (mtd->dev.parent) {
		if (!mtd->owner && mtd->dev.parent->driver)
			mtd->owner = mtd->dev.parent->driver->owner;
		if (!mtd->name)
			mtd->name = dev_name(mtd->dev.parent);
	} else {
		pr_debug("mtd device won't show a device symlink in sysfs\n");
	}

	mtd->orig_flags = mtd->flags;
}