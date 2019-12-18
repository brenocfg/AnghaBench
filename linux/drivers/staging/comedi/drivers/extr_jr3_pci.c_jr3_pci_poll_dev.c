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
struct timer_list {int dummy; } ;
struct jr3_pci_subdev_private {void* next_time_min; } ;
struct jr3_pci_poll_delay {int min; int max; } ;
struct TYPE_2__ {void* expires; } ;
struct jr3_pci_dev_private {TYPE_1__ timer; struct comedi_device* dev; } ;
struct comedi_subdevice {struct jr3_pci_subdev_private* private; } ;
struct comedi_device {int n_subdevices; int /*<<< orphan*/  spinlock; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct jr3_pci_dev_private* devpriv ; 
 struct jr3_pci_dev_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 struct jr3_pci_poll_delay jr3_pci_poll_subdevice (struct comedi_subdevice*) ; 
 void* msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after_eq (unsigned long,void*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void jr3_pci_poll_dev(struct timer_list *t)
{
	struct jr3_pci_dev_private *devpriv = from_timer(devpriv, t, timer);
	struct comedi_device *dev = devpriv->dev;
	struct jr3_pci_subdev_private *spriv;
	struct comedi_subdevice *s;
	unsigned long flags;
	unsigned long now;
	int delay;
	int i;

	spin_lock_irqsave(&dev->spinlock, flags);
	delay = 1000;
	now = jiffies;

	/* Poll all sensors that are ready to be polled */
	for (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		spriv = s->private;

		if (time_after_eq(now, spriv->next_time_min)) {
			struct jr3_pci_poll_delay sub_delay;

			sub_delay = jr3_pci_poll_subdevice(s);

			spriv->next_time_min = jiffies +
					       msecs_to_jiffies(sub_delay.min);

			if (sub_delay.max && sub_delay.max < delay)
				/*
				 * Wake up as late as possible ->
				 * poll as many sensors as possible at once.
				 */
				delay = sub_delay.max;
		}
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	devpriv->timer.expires = jiffies + msecs_to_jiffies(delay);
	add_timer(&devpriv->timer);
}