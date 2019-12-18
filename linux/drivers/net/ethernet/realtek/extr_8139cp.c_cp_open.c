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
struct cp_private {int /*<<< orphan*/  napi; int /*<<< orphan*/  mii_if; TYPE_1__* pdev; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int cp_alloc_rings (struct cp_private*) ; 
 int /*<<< orphan*/  cp_enable_irq (struct cp_private*) ; 
 int /*<<< orphan*/  cp_free_rings (struct cp_private*) ; 
 int /*<<< orphan*/  cp_init_hw (struct cp_private*) ; 
 int /*<<< orphan*/  cp_interrupt ; 
 int /*<<< orphan*/  cp_stop_hw (struct cp_private*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct cp_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_msg_link (struct cp_private*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int cp_open (struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	const int irq = cp->pdev->irq;
	int rc;

	netif_dbg(cp, ifup, dev, "enabling interface\n");

	rc = cp_alloc_rings(cp);
	if (rc)
		return rc;

	napi_enable(&cp->napi);

	cp_init_hw(cp);

	rc = request_irq(irq, cp_interrupt, IRQF_SHARED, dev->name, dev);
	if (rc)
		goto err_out_hw;

	cp_enable_irq(cp);

	netif_carrier_off(dev);
	mii_check_media(&cp->mii_if, netif_msg_link(cp), true);
	netif_start_queue(dev);

	return 0;

err_out_hw:
	napi_disable(&cp->napi);
	cp_stop_hw(cp);
	cp_free_rings(cp);
	return rc;
}