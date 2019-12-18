#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct atl1_adapter {TYPE_1__* pdev; int /*<<< orphan*/  napi; struct net_device* netdev; } ;
typedef  int s32 ;
struct TYPE_3__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int IRQF_SHARED ; 
 int atl1_alloc_rx_buffers (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_check_link (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_clean_rx_ring (struct atl1_adapter*) ; 
 int atl1_configure (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_init_ring_ptrs (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_intr ; 
 int /*<<< orphan*/  atlx_irq_enable (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atlx_restore_vlan (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atlx_set_multi (struct net_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_msg_ifup (struct atl1_adapter*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int pci_enable_msi (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static s32 atl1_up(struct atl1_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err;
	int irq_flags = 0;

	/* hardware has been reset, we need to reload some things */
	atlx_set_multi(netdev);
	atl1_init_ring_ptrs(adapter);
	atlx_restore_vlan(adapter);
	err = atl1_alloc_rx_buffers(adapter);
	if (unlikely(!err))
		/* no RX BUFFER allocated */
		return -ENOMEM;

	if (unlikely(atl1_configure(adapter))) {
		err = -EIO;
		goto err_up;
	}

	err = pci_enable_msi(adapter->pdev);
	if (err) {
		if (netif_msg_ifup(adapter))
			dev_info(&adapter->pdev->dev,
				"Unable to enable MSI: %d\n", err);
		irq_flags |= IRQF_SHARED;
	}

	err = request_irq(adapter->pdev->irq, atl1_intr, irq_flags,
			netdev->name, netdev);
	if (unlikely(err))
		goto err_up;

	napi_enable(&adapter->napi);
	atlx_irq_enable(adapter);
	atl1_check_link(adapter);
	netif_start_queue(netdev);
	return 0;

err_up:
	pci_disable_msi(adapter->pdev);
	/* free rx_buffers */
	atl1_clean_rx_ring(adapter);
	return err;
}