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
struct net_device {int /*<<< orphan*/  name; } ;
struct cas {int hw_running; int opened; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ cas_alloc_rxds (struct cas*) ; 
 int /*<<< orphan*/  cas_clean_rings (struct cas*) ; 
 int /*<<< orphan*/  cas_free_rxds (struct cas*) ; 
 int /*<<< orphan*/  cas_init_hw (struct cas*,int) ; 
 int /*<<< orphan*/  cas_interrupt ; 
 int /*<<< orphan*/  cas_lock_all_save (struct cas*,unsigned long) ; 
 int /*<<< orphan*/  cas_reset (struct cas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_spare_free (struct cas*) ; 
 int /*<<< orphan*/  cas_spare_init (struct cas*) ; 
 int /*<<< orphan*/  cas_spare_recover (struct cas*,int /*<<< orphan*/ ) ; 
 scalar_t__ cas_tx_tiny_alloc (struct cas*) ; 
 int /*<<< orphan*/  cas_tx_tiny_free (struct cas*) ; 
 int /*<<< orphan*/  cas_unlock_all_restore (struct cas*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int cas_open(struct net_device *dev)
{
	struct cas *cp = netdev_priv(dev);
	int hw_was_up, err;
	unsigned long flags;

	mutex_lock(&cp->pm_mutex);

	hw_was_up = cp->hw_running;

	/* The power-management mutex protects the hw_running
	 * etc. state so it is safe to do this bit without cp->lock
	 */
	if (!cp->hw_running) {
		/* Reset the chip */
		cas_lock_all_save(cp, flags);
		/* We set the second arg to cas_reset to zero
		 * because cas_init_hw below will have its second
		 * argument set to non-zero, which will force
		 * autonegotiation to start.
		 */
		cas_reset(cp, 0);
		cp->hw_running = 1;
		cas_unlock_all_restore(cp, flags);
	}

	err = -ENOMEM;
	if (cas_tx_tiny_alloc(cp) < 0)
		goto err_unlock;

	/* alloc rx descriptors */
	if (cas_alloc_rxds(cp) < 0)
		goto err_tx_tiny;

	/* allocate spares */
	cas_spare_init(cp);
	cas_spare_recover(cp, GFP_KERNEL);

	/* We can now request the interrupt as we know it's masked
	 * on the controller. cassini+ has up to 4 interrupts
	 * that can be used, but you need to do explicit pci interrupt
	 * mapping to expose them
	 */
	if (request_irq(cp->pdev->irq, cas_interrupt,
			IRQF_SHARED, dev->name, (void *) dev)) {
		netdev_err(cp->dev, "failed to request irq !\n");
		err = -EAGAIN;
		goto err_spare;
	}

#ifdef USE_NAPI
	napi_enable(&cp->napi);
#endif
	/* init hw */
	cas_lock_all_save(cp, flags);
	cas_clean_rings(cp);
	cas_init_hw(cp, !hw_was_up);
	cp->opened = 1;
	cas_unlock_all_restore(cp, flags);

	netif_start_queue(dev);
	mutex_unlock(&cp->pm_mutex);
	return 0;

err_spare:
	cas_spare_free(cp);
	cas_free_rxds(cp);
err_tx_tiny:
	cas_tx_tiny_free(cp);
err_unlock:
	mutex_unlock(&cp->pm_mutex);
	return err;
}