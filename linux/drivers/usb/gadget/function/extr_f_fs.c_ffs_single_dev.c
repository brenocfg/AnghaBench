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
struct ffs_dev {int single; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ffs_dev_lock () ; 
 int /*<<< orphan*/  ffs_dev_unlock () ; 
 int /*<<< orphan*/  ffs_devices ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 

int ffs_single_dev(struct ffs_dev *dev)
{
	int ret;

	ret = 0;
	ffs_dev_lock();

	if (!list_is_singular(&ffs_devices))
		ret = -EBUSY;
	else
		dev->single = true;

	ffs_dev_unlock();
	return ret;
}