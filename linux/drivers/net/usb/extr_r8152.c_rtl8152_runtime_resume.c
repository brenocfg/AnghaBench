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
struct TYPE_2__ {int /*<<< orphan*/  (* autosuspend_en ) (struct r8152*,int) ;int /*<<< orphan*/  (* disable ) (struct r8152*) ;} ;
struct napi_struct {int dummy; } ;
struct r8152 {int /*<<< orphan*/  flags; TYPE_1__ rtl_ops; int /*<<< orphan*/  intr_urb; struct napi_struct napi; int /*<<< orphan*/  rx_done; struct net_device* netdev; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int IFF_UP ; 
 int LINK_STATUS ; 
 int /*<<< orphan*/  SELECTIVE_SUSPEND ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_enable (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_schedule (struct napi_struct*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int rtl8152_get_speed (struct r8152*) ; 
 int /*<<< orphan*/  rtl_start_rx (struct r8152*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  stub1 (struct r8152*,int) ; 
 int /*<<< orphan*/  stub2 (struct r8152*) ; 
 int /*<<< orphan*/  stub3 (struct r8152*,int) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_runtime_resume(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;

	if (netif_running(netdev) && netdev->flags & IFF_UP) {
		struct napi_struct *napi = &tp->napi;

		tp->rtl_ops.autosuspend_en(tp, false);
		napi_disable(napi);
		set_bit(WORK_ENABLE, &tp->flags);

		if (netif_carrier_ok(netdev)) {
			if (rtl8152_get_speed(tp) & LINK_STATUS) {
				rtl_start_rx(tp);
			} else {
				netif_carrier_off(netdev);
				tp->rtl_ops.disable(tp);
				netif_info(tp, link, netdev, "linking down\n");
			}
		}

		napi_enable(napi);
		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
		smp_mb__after_atomic();

		if (!list_empty(&tp->rx_done))
			napi_schedule(&tp->napi);

		usb_submit_urb(tp->intr_urb, GFP_NOIO);
	} else {
		if (netdev->flags & IFF_UP)
			tp->rtl_ops.autosuspend_en(tp, false);

		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
	}

	return 0;
}