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
struct TYPE_2__ {scalar_t__ expires; } ;
struct cadet {int* rdsbuf; size_t rdsin; int rdsout; TYPE_1__ readtimer; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  lock; scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ cadet_has_rds_data (struct cadet*) ; 
 struct cadet* dev ; 
 struct cadet* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  readtimer ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cadet_handler(struct timer_list *t)
{
	struct cadet *dev = from_timer(dev, t, readtimer);

	/* Service the RDS fifo */
	if (mutex_trylock(&dev->lock)) {
		outb(0x3, dev->io);       /* Select RDS Decoder Control */
		if ((inb(dev->io + 1) & 0x20) != 0)
			pr_err("cadet: RDS fifo overflow\n");
		outb(0x80, dev->io);      /* Select RDS fifo */

		while ((inb(dev->io) & 0x80) != 0) {
			dev->rdsbuf[dev->rdsin] = inb(dev->io + 1);
			if (dev->rdsin + 1 != dev->rdsout)
				dev->rdsin++;
		}
		mutex_unlock(&dev->lock);
	}

	/*
	 * Service pending read
	 */
	if (cadet_has_rds_data(dev))
		wake_up_interruptible(&dev->read_queue);

	/*
	 * Clean up and exit
	 */
	dev->readtimer.expires = jiffies + msecs_to_jiffies(50);
	add_timer(&dev->readtimer);
}