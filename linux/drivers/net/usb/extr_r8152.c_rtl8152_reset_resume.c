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
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct r8152*) ;} ;
struct r8152 {int /*<<< orphan*/  hw_phy_work; TYPE_1__ rtl_ops; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SELECTIVE_SUSPEND ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rtl8152_resume (struct usb_interface*) ; 
 int /*<<< orphan*/  set_ethernet_addr (struct r8152*) ; 
 int /*<<< orphan*/  stub1 (struct r8152*) ; 
 int /*<<< orphan*/  system_long_wq ; 
 struct r8152* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int rtl8152_reset_resume(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);

	clear_bit(SELECTIVE_SUSPEND, &tp->flags);
	tp->rtl_ops.init(tp);
	queue_delayed_work(system_long_wq, &tp->hw_phy_work, 0);
	set_ethernet_addr(tp);
	return rtl8152_resume(intf);
}