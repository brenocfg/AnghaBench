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
struct cmbe {int dummy; } ;
struct cmb_data {int size; struct cmb_data* last_block; struct cmbe* hw_block; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmb_list; struct cmb_data* cmb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMF_ON ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ cmb_area ; 
 int /*<<< orphan*/  cmbe_cache ; 
 int /*<<< orphan*/  cmf_activate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmb_data*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct cmbe*) ; 
 struct cmbe* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_cmbe(struct ccw_device *cdev)
{
	struct cmb_data *cmb_data;
	struct cmbe *cmbe;
	int ret = -ENOMEM;

	cmbe = kmem_cache_zalloc(cmbe_cache, GFP_KERNEL);
	if (!cmbe)
		return ret;

	cmb_data = kzalloc(sizeof(*cmb_data), GFP_KERNEL);
	if (!cmb_data)
		goto out_free;

	cmb_data->last_block = kzalloc(sizeof(struct cmbe), GFP_KERNEL);
	if (!cmb_data->last_block)
		goto out_free;

	cmb_data->size = sizeof(*cmbe);
	cmb_data->hw_block = cmbe;

	spin_lock(&cmb_area.lock);
	spin_lock_irq(cdev->ccwlock);
	if (cdev->private->cmb)
		goto out_unlock;

	cdev->private->cmb = cmb_data;

	/* activate global measurement if this is the first channel */
	if (list_empty(&cmb_area.list))
		cmf_activate(NULL, CMF_ON);
	list_add_tail(&cdev->private->cmb_list, &cmb_area.list);

	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
	return 0;

out_unlock:
	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
	ret = -EBUSY;
out_free:
	if (cmb_data)
		kfree(cmb_data->last_block);
	kfree(cmb_data);
	kmem_cache_free(cmbe_cache, cmbe);

	return ret;
}