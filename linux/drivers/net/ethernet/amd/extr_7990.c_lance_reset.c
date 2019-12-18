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
struct lance_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  WRITERAP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITERDP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int init_restart_lance (struct lance_private*) ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int lance_reset(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	int status;

	/* Stop the lance */
	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STOP);

	load_csrs(lp);
	lance_init_ring(dev);
	netif_trans_update(dev); /* prevent tx timeout */
	status = init_restart_lance(lp);
#ifdef DEBUG_DRIVER
	printk("Lance restart=%d\n", status);
#endif
	return status;
}