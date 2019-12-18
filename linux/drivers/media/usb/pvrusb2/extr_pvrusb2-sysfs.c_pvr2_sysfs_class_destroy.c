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
struct pvr2_sysfs_class {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_sysfs_trace (char*,struct pvr2_sysfs_class*) ; 

void pvr2_sysfs_class_destroy(struct pvr2_sysfs_class *clp)
{
	pvr2_sysfs_trace("Unregistering pvr2_sysfs_class id=%p", clp);
	if (clp)
		class_unregister(&clp->class);
}