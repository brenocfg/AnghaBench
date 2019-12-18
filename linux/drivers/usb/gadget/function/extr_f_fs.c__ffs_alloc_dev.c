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
struct ffs_dev {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 struct ffs_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ _ffs_get_single_dev () ; 
 int /*<<< orphan*/  ffs_devices ; 
 int functionfs_init () ; 
 int /*<<< orphan*/  kfree (struct ffs_dev*) ; 
 struct ffs_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ffs_dev *_ffs_alloc_dev(void)
{
	struct ffs_dev *dev;
	int ret;

	if (_ffs_get_single_dev())
			return ERR_PTR(-EBUSY);

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	if (list_empty(&ffs_devices)) {
		ret = functionfs_init();
		if (ret) {
			kfree(dev);
			return ERR_PTR(ret);
		}
	}

	list_add(&dev->entry, &ffs_devices);

	return dev;
}