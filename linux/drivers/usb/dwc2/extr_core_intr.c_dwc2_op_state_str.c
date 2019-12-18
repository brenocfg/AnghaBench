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
struct dwc2_hsotg {int op_state; } ;

/* Variables and functions */
#define  OTG_STATE_A_HOST 132 
#define  OTG_STATE_A_PERIPHERAL 131 
#define  OTG_STATE_A_SUSPEND 130 
#define  OTG_STATE_B_HOST 129 
#define  OTG_STATE_B_PERIPHERAL 128 

__attribute__((used)) static const char *dwc2_op_state_str(struct dwc2_hsotg *hsotg)
{
	switch (hsotg->op_state) {
	case OTG_STATE_A_HOST:
		return "a_host";
	case OTG_STATE_A_SUSPEND:
		return "a_suspend";
	case OTG_STATE_A_PERIPHERAL:
		return "a_peripheral";
	case OTG_STATE_B_PERIPHERAL:
		return "b_peripheral";
	case OTG_STATE_B_HOST:
		return "b_host";
	default:
		return "unknown";
	}
}