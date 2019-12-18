#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct mISDNtimerdev {int work; scalar_t__ next_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  wait; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct mISDNtimer {int id; TYPE_1__ tl; int /*<<< orphan*/  list; struct mISDNtimerdev* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_expire_timer ; 
 scalar_t__ jiffies ; 
 struct mISDNtimer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
misdn_add_timer(struct mISDNtimerdev *dev, int timeout)
{
	int			id;
	struct mISDNtimer	*timer;

	if (!timeout) {
		dev->work = 1;
		wake_up_interruptible(&dev->wait);
		id = 0;
	} else {
		timer = kzalloc(sizeof(struct mISDNtimer), GFP_KERNEL);
		if (!timer)
			return -ENOMEM;
		timer->dev = dev;
		timer_setup(&timer->tl, dev_expire_timer, 0);
		spin_lock_irq(&dev->lock);
		id = timer->id = dev->next_id++;
		if (dev->next_id < 0)
			dev->next_id = 1;
		list_add_tail(&timer->list, &dev->pending);
		timer->tl.expires = jiffies + ((HZ * (u_long)timeout) / 1000);
		add_timer(&timer->tl);
		spin_unlock_irq(&dev->lock);
	}
	return id;
}