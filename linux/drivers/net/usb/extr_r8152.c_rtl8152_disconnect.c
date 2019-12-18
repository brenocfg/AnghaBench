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
struct TYPE_2__ {int /*<<< orphan*/  (* unload ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  netdev; TYPE_1__ rtl_ops; int /*<<< orphan*/  hw_phy_work; int /*<<< orphan*/  tx_tl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_unplug (struct r8152*) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 struct r8152* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8152_disconnect(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (tp) {
		rtl_set_unplug(tp);

		unregister_netdev(tp->netdev);
		tasklet_kill(&tp->tx_tl);
		cancel_delayed_work_sync(&tp->hw_phy_work);
		tp->rtl_ops.unload(tp);
		free_netdev(tp->netdev);
	}
}