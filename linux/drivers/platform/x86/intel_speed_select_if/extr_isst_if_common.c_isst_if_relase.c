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
struct isst_if_cmd_cb {int /*<<< orphan*/  owner; scalar_t__ registered; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ISST_IF_DEV_MAX ; 
 int /*<<< orphan*/  misc_device_open ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isst_if_cmd_cb* punit_callbacks ; 
 int /*<<< orphan*/  punit_misc_dev_lock ; 

__attribute__((used)) static int isst_if_relase(struct inode *inode, struct file *f)
{
	int i;

	mutex_lock(&punit_misc_dev_lock);
	misc_device_open--;
	for (i = 0; i < ISST_IF_DEV_MAX; ++i) {
		struct isst_if_cmd_cb *cb = &punit_callbacks[i];

		if (cb->registered)
			module_put(cb->owner);
	}
	mutex_unlock(&punit_misc_dev_lock);

	return 0;
}