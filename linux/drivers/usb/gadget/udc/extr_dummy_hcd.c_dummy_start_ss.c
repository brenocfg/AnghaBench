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
struct dummy_hcd {int /*<<< orphan*/  urbp_list; scalar_t__ stream_en_ep; int /*<<< orphan*/  rh_state; int /*<<< orphan*/  timer; } ;
struct TYPE_3__ {int otg_port; } ;
struct TYPE_4__ {int uses_new_polling; TYPE_1__ self; int /*<<< orphan*/  state; int /*<<< orphan*/  power_budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_RH_RUNNING ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POWER_BUDGET_3 ; 
 int /*<<< orphan*/  dev_attr_urbs ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy_hcd*) ; 
 TYPE_2__* dummy_hcd_to_hcd (struct dummy_hcd*) ; 
 int /*<<< orphan*/  dummy_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_start_ss(struct dummy_hcd *dum_hcd)
{
	timer_setup(&dum_hcd->timer, dummy_timer, 0);
	dum_hcd->rh_state = DUMMY_RH_RUNNING;
	dum_hcd->stream_en_ep = 0;
	INIT_LIST_HEAD(&dum_hcd->urbp_list);
	dummy_hcd_to_hcd(dum_hcd)->power_budget = POWER_BUDGET_3;
	dummy_hcd_to_hcd(dum_hcd)->state = HC_STATE_RUNNING;
	dummy_hcd_to_hcd(dum_hcd)->uses_new_polling = 1;
#ifdef CONFIG_USB_OTG
	dummy_hcd_to_hcd(dum_hcd)->self.otg_port = 1;
#endif
	return 0;

	/* FIXME 'urbs' should be a per-device thing, maybe in usbcore */
	return device_create_file(dummy_dev(dum_hcd), &dev_attr_urbs);
}