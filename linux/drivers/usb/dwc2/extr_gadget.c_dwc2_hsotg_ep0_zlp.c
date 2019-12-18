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
struct dwc2_hsotg {TYPE_1__** eps_out; int /*<<< orphan*/  ep0_state; } ;
struct TYPE_2__ {int dir_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_EP0_STATUS_IN ; 
 int /*<<< orphan*/  DWC2_EP0_STATUS_OUT ; 
 int /*<<< orphan*/  dwc2_hsotg_program_zlp (struct dwc2_hsotg*,TYPE_1__*) ; 

__attribute__((used)) static void dwc2_hsotg_ep0_zlp(struct dwc2_hsotg *hsotg, bool dir_in)
{
	/* eps_out[0] is used in both directions */
	hsotg->eps_out[0]->dir_in = dir_in;
	hsotg->ep0_state = dir_in ? DWC2_EP0_STATUS_IN : DWC2_EP0_STATUS_OUT;

	dwc2_hsotg_program_zlp(hsotg, hsotg->eps_out[0]);
}