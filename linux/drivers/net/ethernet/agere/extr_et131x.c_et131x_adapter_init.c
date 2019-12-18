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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct et131x_adapter {int registry_jumbo_packet; int /*<<< orphan*/  addr; int /*<<< orphan*/  rcv_lock; int /*<<< orphan*/  tcb_ready_qlock; int /*<<< orphan*/  tcb_send_qlock; struct net_device* netdev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int const*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct et131x_adapter *et131x_adapter_init(struct net_device *netdev,
						  struct pci_dev *pdev)
{
	static const u8 default_mac[] = { 0x00, 0x05, 0x3d, 0x00, 0x02, 0x00 };

	struct et131x_adapter *adapter;

	adapter = netdev_priv(netdev);
	adapter->pdev = pci_dev_get(pdev);
	adapter->netdev = netdev;

	spin_lock_init(&adapter->tcb_send_qlock);
	spin_lock_init(&adapter->tcb_ready_qlock);
	spin_lock_init(&adapter->rcv_lock);

	adapter->registry_jumbo_packet = 1514;	/* 1514-9216 */

	ether_addr_copy(adapter->addr, default_mac);

	return adapter;
}