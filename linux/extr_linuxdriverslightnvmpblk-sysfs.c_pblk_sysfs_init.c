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
struct pblk {int /*<<< orphan*/  kobj; int /*<<< orphan*/  disk; } ;
struct gendisk {struct pblk* private_data; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 struct device* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int /*<<< orphan*/  pblk_ktype ; 

int pblk_sysfs_init(struct gendisk *tdisk)
{
	struct pblk *pblk = tdisk->private_data;
	struct device *parent_dev = disk_to_dev(pblk->disk);
	int ret;

	ret = kobject_init_and_add(&pblk->kobj, &pblk_ktype,
					kobject_get(&parent_dev->kobj),
					"%s", "pblk");
	if (ret) {
		pblk_err(pblk, "could not register\n");
		return ret;
	}

	kobject_uevent(&pblk->kobj, KOBJ_ADD);
	return 0;
}