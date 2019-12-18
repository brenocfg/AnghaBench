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
struct napi_struct {int dummy; } ;
struct r8152 {int /*<<< orphan*/  tx_tl; TYPE_1__ rtl_ops; int /*<<< orphan*/  schedule; int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  flags; struct napi_struct napi; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_enable (struct napi_struct*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_system_suspend(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;

	netif_device_detach(netdev);

	if (netif_running(netdev) && test_bit(WORK_ENABLE, &tp->flags)) {
		struct napi_struct *napi = &tp->napi;

		clear_bit(WORK_ENABLE, &tp->flags);
		usb_kill_urb(tp->intr_urb);
		tasklet_disable(&tp->tx_tl);
		napi_disable(napi);
		cancel_delayed_work_sync(&tp->schedule);
		tp->rtl_ops.down(tp);
		napi_enable(napi);
		tasklet_enable(&tp->tx_tl);
	}

	return 0;
}