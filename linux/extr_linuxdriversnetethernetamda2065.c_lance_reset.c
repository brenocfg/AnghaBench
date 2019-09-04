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
struct lance_regs {int /*<<< orphan*/  rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {struct lance_regs* ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int init_restart_lance (struct lance_private*) ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 

__attribute__((used)) static inline int lance_reset(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_regs *ll = lp->ll;
	int status;

	/* Stop the lance */
	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_STOP;

	load_csrs(lp);

	lance_init_ring(dev);
	netif_trans_update(dev); /* prevent tx timeout */
	netif_start_queue(dev);

	status = init_restart_lance(lp);
	netdev_dbg(dev, "Lance restart=%d\n", status);

	return status;
}