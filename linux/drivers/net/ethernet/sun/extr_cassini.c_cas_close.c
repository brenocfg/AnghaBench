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
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/  pm_mutex; TYPE_1__* pdev; scalar_t__ opened; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cas_begin_auto_negotiation (struct cas*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cas_clean_rings (struct cas*) ; 
 int /*<<< orphan*/  cas_free_rxds (struct cas*) ; 
 int /*<<< orphan*/  cas_lock_all_save (struct cas*,unsigned long) ; 
 int /*<<< orphan*/  cas_phy_init (struct cas*) ; 
 int /*<<< orphan*/  cas_reset (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_spare_free (struct cas*) ; 
 int /*<<< orphan*/  cas_tx_tiny_free (struct cas*) ; 
 int /*<<< orphan*/  cas_unlock_all_restore (struct cas*,unsigned long) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int cas_close(struct net_device *dev)
{
	unsigned long flags;
	struct cas *cp = netdev_priv(dev);

#ifdef USE_NAPI
	napi_disable(&cp->napi);
#endif
	/* Make sure we don't get distracted by suspend/resume */
	mutex_lock(&cp->pm_mutex);

	netif_stop_queue(dev);

	/* Stop traffic, mark us closed */
	cas_lock_all_save(cp, flags);
	cp->opened = 0;
	cas_reset(cp, 0);
	cas_phy_init(cp);
	cas_begin_auto_negotiation(cp, NULL);
	cas_clean_rings(cp);
	cas_unlock_all_restore(cp, flags);

	free_irq(cp->pdev->irq, (void *) dev);
	cas_spare_free(cp);
	cas_free_rxds(cp);
	cas_tx_tiny_free(cp);
	mutex_unlock(&cp->pm_mutex);
	return 0;
}