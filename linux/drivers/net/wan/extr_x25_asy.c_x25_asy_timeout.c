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
struct x25_asy {int /*<<< orphan*/  lock; TYPE_1__* tty; scalar_t__ xleft; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,char*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_chars_in_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  x25_asy_unlock (struct x25_asy*) ; 

__attribute__((used)) static void x25_asy_timeout(struct net_device *dev)
{
	struct x25_asy *sl = netdev_priv(dev);

	spin_lock(&sl->lock);
	if (netif_queue_stopped(dev)) {
		/* May be we must check transmitter timeout here ?
		 *      14 Oct 1994 Dmitry Gorodchanin.
		 */
		netdev_warn(dev, "transmit timed out, %s?\n",
			    (tty_chars_in_buffer(sl->tty) || sl->xleft) ?
			    "bad line quality" : "driver error");
		sl->xleft = 0;
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
		x25_asy_unlock(sl);
	}
	spin_unlock(&sl->lock);
}