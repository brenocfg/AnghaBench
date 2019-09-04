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
struct nvm_geo {int /*<<< orphan*/  all_luns; } ;
struct nvm_dev {int /*<<< orphan*/  lun_map; int /*<<< orphan*/  lock; int /*<<< orphan*/  mlock; int /*<<< orphan*/  targets; int /*<<< orphan*/  area_list; struct nvm_geo geo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nvm_register_map (struct nvm_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvm_core_init(struct nvm_dev *dev)
{
	struct nvm_geo *geo = &dev->geo;
	int ret;

	dev->lun_map = kcalloc(BITS_TO_LONGS(geo->all_luns),
					sizeof(unsigned long), GFP_KERNEL);
	if (!dev->lun_map)
		return -ENOMEM;

	INIT_LIST_HEAD(&dev->area_list);
	INIT_LIST_HEAD(&dev->targets);
	mutex_init(&dev->mlock);
	spin_lock_init(&dev->lock);

	ret = nvm_register_map(dev);
	if (ret)
		goto err_fmtype;

	return 0;
err_fmtype:
	kfree(dev->lun_map);
	return ret;
}