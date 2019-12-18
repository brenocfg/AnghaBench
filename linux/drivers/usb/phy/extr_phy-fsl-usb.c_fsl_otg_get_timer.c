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
struct fsl_otg_timer {int dummy; } ;
typedef  enum otg_fsm_timer { ____Placeholder_otg_fsm_timer } otg_fsm_timer ;

/* Variables and functions */
#define  A_AIDL_BDIS 134 
#define  A_WAIT_BCON 133 
#define  A_WAIT_ENUM 132 
#define  A_WAIT_VRISE 131 
#define  B_ASE0_BRST 130 
#define  B_SE0_SRP 129 
#define  B_SRP_FAIL 128 
 struct fsl_otg_timer* a_wait_vrise_tmr ; 

__attribute__((used)) static struct fsl_otg_timer *fsl_otg_get_timer(enum otg_fsm_timer t)
{
	struct fsl_otg_timer *timer;

	/* REVISIT: use array of pointers to timers instead */
	switch (t) {
	case A_WAIT_VRISE:
		timer = a_wait_vrise_tmr;
		break;
	case A_WAIT_BCON:
		timer = a_wait_vrise_tmr;
		break;
	case A_AIDL_BDIS:
		timer = a_wait_vrise_tmr;
		break;
	case B_ASE0_BRST:
		timer = a_wait_vrise_tmr;
		break;
	case B_SE0_SRP:
		timer = a_wait_vrise_tmr;
		break;
	case B_SRP_FAIL:
		timer = a_wait_vrise_tmr;
		break;
	case A_WAIT_ENUM:
		timer = a_wait_vrise_tmr;
		break;
	default:
		timer = NULL;
	}

	return timer;
}