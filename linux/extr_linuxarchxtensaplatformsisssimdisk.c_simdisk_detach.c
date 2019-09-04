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
struct simdisk {scalar_t__ users; int fd; int /*<<< orphan*/  lock; int /*<<< orphan*/ * filename; TYPE_1__* gd; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ simc_close (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int simdisk_detach(struct simdisk *dev)
{
	int err = 0;

	spin_lock(&dev->lock);

	if (dev->users != 0) {
		err = -EBUSY;
	} else if (dev->fd != -1) {
		if (simc_close(dev->fd)) {
			pr_err("SIMDISK: error closing %s: %d\n",
					dev->filename, errno);
			err = -EIO;
		} else {
			pr_info("SIMDISK: %s detached from %s\n",
					dev->gd->disk_name, dev->filename);
			dev->fd = -1;
			kfree(dev->filename);
			dev->filename = NULL;
		}
	}
	spin_unlock(&dev->lock);
	return err;
}