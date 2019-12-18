#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfd_alloc_struct (int /*<<< orphan*/ ) ; 
 TYPE_2__* kfd_device ; 
 int /*<<< orphan*/  kfd_procfs_shutdown () ; 
 int kobject_init_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_1__ procfs ; 
 int /*<<< orphan*/  procfs_type ; 

void kfd_procfs_init(void)
{
	int ret = 0;

	procfs.kobj = kfd_alloc_struct(procfs.kobj);
	if (!procfs.kobj)
		return;

	ret = kobject_init_and_add(procfs.kobj, &procfs_type,
				   &kfd_device->kobj, "proc");
	if (ret) {
		pr_warn("Could not create procfs proc folder");
		/* If we fail to create the procfs, clean up */
		kfd_procfs_shutdown();
	}
}