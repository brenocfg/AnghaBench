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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  timer_service; struct net_device* netdev; struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_com_delete_debug_area (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_delete_host_info (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_destroy_interrupt_moderation (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_rss_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_destroy_device (struct ena_adapter*,int) ; 
 int /*<<< orphan*/  ena_release_bars (struct ena_com_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ena_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  vfree (struct ena_com_dev*) ; 

__attribute__((used)) static void ena_remove(struct pci_dev *pdev)
{
	struct ena_adapter *adapter = pci_get_drvdata(pdev);
	struct ena_com_dev *ena_dev;
	struct net_device *netdev;

	ena_dev = adapter->ena_dev;
	netdev = adapter->netdev;

#ifdef CONFIG_RFS_ACCEL
	if ((adapter->msix_vecs >= 1) && (netdev->rx_cpu_rmap)) {
		free_irq_cpu_rmap(netdev->rx_cpu_rmap);
		netdev->rx_cpu_rmap = NULL;
	}
#endif /* CONFIG_RFS_ACCEL */
	del_timer_sync(&adapter->timer_service);

	cancel_work_sync(&adapter->reset_task);

	unregister_netdev(netdev);

	/* If the device is running then we want to make sure the device will be
	 * reset to make sure no more events will be issued by the device.
	 */
	if (test_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags))
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);

	rtnl_lock();
	ena_destroy_device(adapter, true);
	rtnl_unlock();

	free_netdev(netdev);

	ena_com_rss_destroy(ena_dev);

	ena_com_delete_debug_area(ena_dev);

	ena_com_delete_host_info(ena_dev);

	ena_release_bars(ena_dev, pdev);

	pci_disable_device(pdev);

	ena_com_destroy_interrupt_moderation(ena_dev);

	vfree(ena_dev);
}