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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {scalar_t__ media; scalar_t__ c_media; int tx_enable; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_TPD ; 
 int /*<<< orphan*/  POLL_DEMAND ; 
 int /*<<< orphan*/  de4x5_dbg_media (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_rst_desc_ring (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_setup_intr (struct net_device*) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
de4x5_init_connection(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    u_long flags = 0;

    if (lp->media != lp->c_media) {
        de4x5_dbg_media(dev);
	lp->c_media = lp->media;          /* Stop scrolling media messages */
    }

    spin_lock_irqsave(&lp->lock, flags);
    de4x5_rst_desc_ring(dev);
    de4x5_setup_intr(dev);
    lp->tx_enable = true;
    spin_unlock_irqrestore(&lp->lock, flags);
    outl(POLL_DEMAND, DE4X5_TPD);

    netif_wake_queue(dev);
}