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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSED ; 
 int /*<<< orphan*/  DE4X5_STS ; 
 int DEBUG_CLOSE ; 
 int /*<<< orphan*/  DISABLE_IRQs ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  STOP_DE4X5 ; 
 int de4x5_debug ; 
 int /*<<< orphan*/  de4x5_free_rx_buffs (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_free_tx_buffs (struct net_device*) ; 
 int /*<<< orphan*/  disable_ast (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yawn (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
de4x5_close(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    s32 imr, omr;

    disable_ast(dev);

    netif_stop_queue(dev);

    if (de4x5_debug & DEBUG_CLOSE) {
	printk("%s: Shutting down ethercard, status was %8.8x.\n",
	       dev->name, inl(DE4X5_STS));
    }

    /*
    ** We stop the DE4X5 here... mask interrupts and stop TX & RX
    */
    DISABLE_IRQs;
    STOP_DE4X5;

    /* Free the associated irq */
    free_irq(dev->irq, dev);
    lp->state = CLOSED;

    /* Free any socket buffers */
    de4x5_free_rx_buffs(dev);
    de4x5_free_tx_buffs(dev);

    /* Put the adapter to sleep to save power */
    yawn(dev, SLEEP);

    return 0;
}