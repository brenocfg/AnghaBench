#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {void* watchdog_timeo; } ;
struct ena_admin_ena_hw_hints {int admin_completion_tx_timeout; int mmio_read_timeout; scalar_t__ missing_tx_completion_timeout; scalar_t__ netdev_wd_timeout; scalar_t__ driver_watchdog_timeout; scalar_t__ missed_tx_completion_count_threshold_to_reset; } ;
struct ena_adapter {void* keep_alive_timeout; void* missing_tx_completion_to; scalar_t__ missing_tx_completion_threshold; TYPE_3__* ena_dev; struct net_device* netdev; } ;
struct TYPE_5__ {int reg_read_to; } ;
struct TYPE_4__ {int completion_timeout; } ;
struct TYPE_6__ {TYPE_2__ mmio_read; TYPE_1__ admin_queue; } ;

/* Variables and functions */
 scalar_t__ ENA_HW_HINTS_NO_TIMEOUT ; 
 void* msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void ena_update_hints(struct ena_adapter *adapter,
			     struct ena_admin_ena_hw_hints *hints)
{
	struct net_device *netdev = adapter->netdev;

	if (hints->admin_completion_tx_timeout)
		adapter->ena_dev->admin_queue.completion_timeout =
			hints->admin_completion_tx_timeout * 1000;

	if (hints->mmio_read_timeout)
		/* convert to usec */
		adapter->ena_dev->mmio_read.reg_read_to =
			hints->mmio_read_timeout * 1000;

	if (hints->missed_tx_completion_count_threshold_to_reset)
		adapter->missing_tx_completion_threshold =
			hints->missed_tx_completion_count_threshold_to_reset;

	if (hints->missing_tx_completion_timeout) {
		if (hints->missing_tx_completion_timeout == ENA_HW_HINTS_NO_TIMEOUT)
			adapter->missing_tx_completion_to = ENA_HW_HINTS_NO_TIMEOUT;
		else
			adapter->missing_tx_completion_to =
				msecs_to_jiffies(hints->missing_tx_completion_timeout);
	}

	if (hints->netdev_wd_timeout)
		netdev->watchdog_timeo = msecs_to_jiffies(hints->netdev_wd_timeout);

	if (hints->driver_watchdog_timeout) {
		if (hints->driver_watchdog_timeout == ENA_HW_HINTS_NO_TIMEOUT)
			adapter->keep_alive_timeout = ENA_HW_HINTS_NO_TIMEOUT;
		else
			adapter->keep_alive_timeout =
				msecs_to_jiffies(hints->driver_watchdog_timeout);
	}
}