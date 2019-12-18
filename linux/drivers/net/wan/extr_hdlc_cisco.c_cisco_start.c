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
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct cisco_state {TYPE_1__ timer; struct net_device* dev; int /*<<< orphan*/  lock; scalar_t__ rxseq; scalar_t__ txseq; scalar_t__ up; } ;
typedef  int /*<<< orphan*/  hdlc_device ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  cisco_timer ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cisco_state* state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cisco_start(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	struct cisco_state *st = state(hdlc);
	unsigned long flags;

	spin_lock_irqsave(&st->lock, flags);
	st->up = st->txseq = st->rxseq = 0;
	spin_unlock_irqrestore(&st->lock, flags);

	st->dev = dev;
	timer_setup(&st->timer, cisco_timer, 0);
	st->timer.expires = jiffies + HZ; /* First poll after 1 s */
	add_timer(&st->timer);
}