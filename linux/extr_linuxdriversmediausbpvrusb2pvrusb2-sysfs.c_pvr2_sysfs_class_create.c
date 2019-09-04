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
struct TYPE_2__ {char* name; int /*<<< orphan*/  dev_release; int /*<<< orphan*/  class_release; } ;
struct pvr2_sysfs_class {TYPE_1__ class; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ class_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct pvr2_sysfs_class*) ; 
 struct pvr2_sysfs_class* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_sysfs_class_release ; 
 int /*<<< orphan*/  pvr2_sysfs_release ; 
 int /*<<< orphan*/  pvr2_sysfs_trace (char*,struct pvr2_sysfs_class*) ; 

struct pvr2_sysfs_class *pvr2_sysfs_class_create(void)
{
	struct pvr2_sysfs_class *clp;
	clp = kzalloc(sizeof(*clp),GFP_KERNEL);
	if (!clp) return clp;
	pvr2_sysfs_trace("Creating and registering pvr2_sysfs_class id=%p",
			 clp);
	clp->class.name = "pvrusb2";
	clp->class.class_release = pvr2_sysfs_class_release;
	clp->class.dev_release = pvr2_sysfs_release;
	if (class_register(&clp->class)) {
		pvr2_sysfs_trace(
			"Registration failed for pvr2_sysfs_class id=%p",clp);
		kfree(clp);
		clp = NULL;
	}
	return clp;
}