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
struct net_device {int dummy; } ;
struct lance_private {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  WRITERAP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITERDP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

int lance_close(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);

	netif_stop_queue(dev);

	/* Stop the LANCE */
	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STOP);

	free_irq(lp->irq, dev);

	return 0;
}