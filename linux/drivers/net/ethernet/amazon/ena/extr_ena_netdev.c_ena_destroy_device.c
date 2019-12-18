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
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int dev_up_before_reset; int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_reason; struct ena_com_dev* ena_dev; int /*<<< orphan*/  timer_service; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_NORMAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_com_abort_admin_commands (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_admin_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_dev_reset (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_destroy (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_set_admin_running_state (struct ena_com_dev*,int) ; 
 int /*<<< orphan*/  ena_com_wait_for_abort_completion (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_disable_msix (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_down (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_mgmnt_irq (struct ena_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ena_destroy_device(struct ena_adapter *adapter, bool graceful)
{
	struct net_device *netdev = adapter->netdev;
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	bool dev_up;

	if (!test_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags))
		return;

	netif_carrier_off(netdev);

	del_timer_sync(&adapter->timer_service);

	dev_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);
	adapter->dev_up_before_reset = dev_up;
	if (!graceful)
		ena_com_set_admin_running_state(ena_dev, false);

	if (test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		ena_down(adapter);

	/* Stop the device from sending AENQ events (in case reset flag is set
	 *  and device is up, ena_down() already reset the device.
	 */
	if (!(test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags) && dev_up))
		ena_com_dev_reset(adapter->ena_dev, adapter->reset_reason);

	ena_free_mgmnt_irq(adapter);

	ena_disable_msix(adapter);

	ena_com_abort_admin_commands(ena_dev);

	ena_com_wait_for_abort_completion(ena_dev);

	ena_com_admin_destroy(ena_dev);

	ena_com_mmio_reg_read_request_destroy(ena_dev);

	adapter->reset_reason = ENA_REGS_RESET_NORMAL;

	clear_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	clear_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);
}