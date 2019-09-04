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
struct pvr2_sysfs_ctl_item {int /*<<< orphan*/  grp; scalar_t__ created_ok; struct pvr2_sysfs_ctl_item* item_next; } ;
struct pvr2_sysfs {TYPE_1__* class_dev; struct pvr2_sysfs_ctl_item* item_first; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pvr2_sysfs_ctl_item*) ; 
 int /*<<< orphan*/  pvr2_sysfs_trace (char*,struct pvr2_sysfs_ctl_item*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_sysfs_tear_down_controls(struct pvr2_sysfs *sfp)
{
	struct pvr2_sysfs_ctl_item *cip1,*cip2;
	for (cip1 = sfp->item_first; cip1; cip1 = cip2) {
		cip2 = cip1->item_next;
		if (cip1->created_ok) {
			sysfs_remove_group(&sfp->class_dev->kobj,&cip1->grp);
		}
		pvr2_sysfs_trace("Destroying pvr2_sysfs_ctl_item id=%p",cip1);
		kfree(cip1);
	}
}