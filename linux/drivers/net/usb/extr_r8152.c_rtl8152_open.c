#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* up ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; TYPE_2__ pm_notifier; int /*<<< orphan*/  tx_tl; int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  flags; TYPE_1__ rtl_ops; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int alloc_all_mem (struct r8152*) ; 
 int /*<<< orphan*/  free_all_mem (struct r8152*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  register_pm_notifier (TYPE_2__*) ; 
 int /*<<< orphan*/  rtl_notifier ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_open(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);
	int res = 0;

	res = alloc_all_mem(tp);
	if (res)
		goto out;

	res = usb_autopm_get_interface(tp->intf);
	if (res < 0)
		goto out_free;

	mutex_lock(&tp->control);

	tp->rtl_ops.up(tp);

	netif_carrier_off(netdev);
	netif_start_queue(netdev);
	set_bit(WORK_ENABLE, &tp->flags);

	res = usb_submit_urb(tp->intr_urb, GFP_KERNEL);
	if (res) {
		if (res == -ENODEV)
			netif_device_detach(tp->netdev);
		netif_warn(tp, ifup, netdev, "intr_urb submit failed: %d\n",
			   res);
		goto out_unlock;
	}
	napi_enable(&tp->napi);
	tasklet_enable(&tp->tx_tl);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);
#ifdef CONFIG_PM_SLEEP
	tp->pm_notifier.notifier_call = rtl_notifier;
	register_pm_notifier(&tp->pm_notifier);
#endif
	return 0;

out_unlock:
	mutex_unlock(&tp->control);
	usb_autopm_put_interface(tp->intf);
out_free:
	free_all_mem(tp);
out:
	return res;
}