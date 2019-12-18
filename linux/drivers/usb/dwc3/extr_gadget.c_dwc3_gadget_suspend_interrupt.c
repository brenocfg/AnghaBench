#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dwc3 {int link_state; } ;
typedef  enum dwc3_link_state { ____Placeholder_dwc3_link_state } dwc3_link_state ;

/* Variables and functions */
 unsigned int DWC3_LINK_STATE_MASK ; 
 int DWC3_LINK_STATE_U3 ; 
 int /*<<< orphan*/  dwc3_suspend_gadget (struct dwc3*) ; 

__attribute__((used)) static void dwc3_gadget_suspend_interrupt(struct dwc3 *dwc,
					  unsigned int evtinfo)
{
	enum dwc3_link_state next = evtinfo & DWC3_LINK_STATE_MASK;

	if (dwc->link_state != next && next == DWC3_LINK_STATE_U3)
		dwc3_suspend_gadget(dwc);

	dwc->link_state = next;
}