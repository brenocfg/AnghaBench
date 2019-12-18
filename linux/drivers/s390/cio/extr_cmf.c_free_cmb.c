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
struct cmb_data {struct cmb_data* last_block; } ;
struct cmb {int dummy; } ;
struct ccw_device_private {int /*<<< orphan*/  cmb_list; struct cmb_data* cmb; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; struct ccw_device_private* private; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int num_channels; int /*<<< orphan*/  lock; int /*<<< orphan*/ * mem; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMF_OFF ; 
 TYPE_1__ cmb_area ; 
 int /*<<< orphan*/  cmf_activate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct cmb_data*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_cmb(struct ccw_device *cdev)
{
	struct ccw_device_private *priv;
	struct cmb_data *cmb_data;

	spin_lock(&cmb_area.lock);
	spin_lock_irq(cdev->ccwlock);

	priv = cdev->private;
	cmb_data = priv->cmb;
	priv->cmb = NULL;
	if (cmb_data)
		kfree(cmb_data->last_block);
	kfree(cmb_data);
	list_del_init(&priv->cmb_list);

	if (list_empty(&cmb_area.list)) {
		ssize_t size;
		size = sizeof(struct cmb) * cmb_area.num_channels;
		cmf_activate(NULL, CMF_OFF);
		free_pages((unsigned long)cmb_area.mem, get_order(size));
		cmb_area.mem = NULL;
	}
	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
}