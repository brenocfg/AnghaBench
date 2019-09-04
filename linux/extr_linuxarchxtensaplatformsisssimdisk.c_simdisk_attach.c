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
struct simdisk {int fd; int size; char const* filename; int /*<<< orphan*/  lock; TYPE_1__* gd; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  set_capacity (TYPE_1__*,int) ; 
 int simc_lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int simc_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int simdisk_attach(struct simdisk *dev, const char *filename)
{
	int err = 0;

	filename = kstrdup(filename, GFP_KERNEL);
	if (filename == NULL)
		return -ENOMEM;

	spin_lock(&dev->lock);

	if (dev->fd != -1) {
		err = -EBUSY;
		goto out;
	}
	dev->fd = simc_open(filename, O_RDWR, 0);
	if (dev->fd == -1) {
		pr_err("SIMDISK: Can't open %s: %d\n", filename, errno);
		err = -ENODEV;
		goto out;
	}
	dev->size = simc_lseek(dev->fd, 0, SEEK_END);
	set_capacity(dev->gd, dev->size >> SECTOR_SHIFT);
	dev->filename = filename;
	pr_info("SIMDISK: %s=%s\n", dev->gd->disk_name, dev->filename);
out:
	if (err)
		kfree(filename);
	spin_unlock(&dev->lock);

	return err;
}