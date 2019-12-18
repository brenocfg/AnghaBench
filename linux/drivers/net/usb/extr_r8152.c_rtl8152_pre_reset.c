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
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  control; TYPE_1__ rtl_ops; int /*<<< orphan*/  schedule; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  flags; int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_tl; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 struct r8152* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_pre_reset(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	struct net_device *netdev;

	if (!tp)
		return 0;

	netdev = tp->netdev;
	if (!netif_running(netdev))
		return 0;

	netif_stop_queue(netdev);
	tasklet_disable(&tp->tx_tl);
	napi_disable(&tp->napi);
	clear_bit(WORK_ENABLE, &tp->flags);
	usb_kill_urb(tp->intr_urb);
	cancel_delayed_work_sync(&tp->schedule);
	if (netif_carrier_ok(netdev)) {
		mutex_lock(&tp->control);
		tp->rtl_ops.disable(tp);
		mutex_unlock(&tp->control);
	}

	return 0;
}