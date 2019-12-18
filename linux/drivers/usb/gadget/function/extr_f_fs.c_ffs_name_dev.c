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
struct ffs_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 struct ffs_dev* _ffs_do_find_dev (char const*) ; 
 int /*<<< orphan*/  ffs_dev_lock () ; 
 int /*<<< orphan*/  ffs_dev_unlock () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int ffs_name_dev(struct ffs_dev *dev, const char *name)
{
	struct ffs_dev *existing;
	int ret = 0;

	ffs_dev_lock();

	existing = _ffs_do_find_dev(name);
	if (!existing)
		strlcpy(dev->name, name, ARRAY_SIZE(dev->name));
	else if (existing != dev)
		ret = -EBUSY;

	ffs_dev_unlock();

	return ret;
}