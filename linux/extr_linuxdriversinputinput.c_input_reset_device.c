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
struct input_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_dev_release_keys (struct input_dev*) ; 
 int /*<<< orphan*/  input_dev_toggle (struct input_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void input_reset_device(struct input_dev *dev)
{
	unsigned long flags;

	mutex_lock(&dev->mutex);
	spin_lock_irqsave(&dev->event_lock, flags);

	input_dev_toggle(dev, true);
	input_dev_release_keys(dev);

	spin_unlock_irqrestore(&dev->event_lock, flags);
	mutex_unlock(&dev->mutex);
}