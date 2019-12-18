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
struct wl3501_card {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl3501_ack_interrupt (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_block_interrupt (struct wl3501_card*) ; 
 int /*<<< orphan*/  wl3501_rx_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  wl3501_unblock_interrupt (struct wl3501_card*) ; 

__attribute__((used)) static irqreturn_t wl3501_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct wl3501_card *this;

	this = netdev_priv(dev);
	spin_lock(&this->lock);
	wl3501_ack_interrupt(this);
	wl3501_block_interrupt(this);
	wl3501_rx_interrupt(dev);
	wl3501_unblock_interrupt(this);
	spin_unlock(&this->lock);

	return IRQ_HANDLED;
}