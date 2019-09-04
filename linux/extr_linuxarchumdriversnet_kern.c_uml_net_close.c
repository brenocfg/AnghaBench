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
struct uml_net_private {int fd; int /*<<< orphan*/  list; int /*<<< orphan*/  user; int /*<<< orphan*/  (* close ) (int,int /*<<< orphan*/ *) ;} ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  opened_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  um_free_irq (int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int uml_net_close(struct net_device *dev)
{
	struct uml_net_private *lp = netdev_priv(dev);

	netif_stop_queue(dev);

	um_free_irq(dev->irq, dev);
	if (lp->close != NULL)
		(*lp->close)(lp->fd, &lp->user);
	lp->fd = -1;

	spin_lock(&opened_lock);
	list_del(&lp->list);
	spin_unlock(&opened_lock);

	return 0;
}