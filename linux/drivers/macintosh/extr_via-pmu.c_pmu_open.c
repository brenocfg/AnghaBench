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
struct pmu_private {int /*<<< orphan*/  list; scalar_t__ backlight_locker; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; scalar_t__ rb_put; scalar_t__ rb_get; } ;
struct inode {int dummy; } ;
struct file {struct pmu_private* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  all_pmu_pvt ; 
 int /*<<< orphan*/  all_pvt_lock ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct pmu_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_info_proc_mutex ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
pmu_open(struct inode *inode, struct file *file)
{
	struct pmu_private *pp;
	unsigned long flags;

	pp = kmalloc(sizeof(struct pmu_private), GFP_KERNEL);
	if (!pp)
		return -ENOMEM;
	pp->rb_get = pp->rb_put = 0;
	spin_lock_init(&pp->lock);
	init_waitqueue_head(&pp->wait);
	mutex_lock(&pmu_info_proc_mutex);
	spin_lock_irqsave(&all_pvt_lock, flags);
#if defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_PMAC_BACKLIGHT)
	pp->backlight_locker = 0;
#endif
	list_add(&pp->list, &all_pmu_pvt);
	spin_unlock_irqrestore(&all_pvt_lock, flags);
	file->private_data = pp;
	mutex_unlock(&pmu_info_proc_mutex);
	return 0;
}