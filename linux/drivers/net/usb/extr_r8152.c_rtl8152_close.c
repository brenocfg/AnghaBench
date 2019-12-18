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
struct TYPE_2__ {int /*<<< orphan*/  (* down ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; TYPE_1__ rtl_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  schedule; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_tl; int /*<<< orphan*/  pm_notifier; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_all_mem (struct r8152*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl_drop_queued_tx (struct r8152*) ; 
 int /*<<< orphan*/  rtl_stop_rx (struct r8152*) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_close(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);
	int res = 0;

#ifdef CONFIG_PM_SLEEP
	unregister_pm_notifier(&tp->pm_notifier);
#endif
	tasklet_disable(&tp->tx_tl);
	napi_disable(&tp->napi);
	clear_bit(WORK_ENABLE, &tp->flags);
	usb_kill_urb(tp->intr_urb);
	cancel_delayed_work_sync(&tp->schedule);
	netif_stop_queue(netdev);

	res = usb_autopm_get_interface(tp->intf);
	if (res < 0 || test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		rtl_stop_rx(tp);
	} else {
		mutex_lock(&tp->control);

		tp->rtl_ops.down(tp);

		mutex_unlock(&tp->control);

		usb_autopm_put_interface(tp->intf);
	}

	free_all_mem(tp);

	return res;
}