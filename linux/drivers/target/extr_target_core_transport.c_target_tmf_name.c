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
typedef  enum tcm_tmreq_table { ____Placeholder_tcm_tmreq_table } tcm_tmreq_table ;

/* Variables and functions */
#define  TMR_ABORT_TASK 135 
#define  TMR_ABORT_TASK_SET 134 
#define  TMR_CLEAR_ACA 133 
#define  TMR_CLEAR_TASK_SET 132 
#define  TMR_LUN_RESET 131 
#define  TMR_TARGET_COLD_RESET 130 
#define  TMR_TARGET_WARM_RESET 129 
#define  TMR_UNKNOWN 128 

__attribute__((used)) static const char *target_tmf_name(enum tcm_tmreq_table tmf)
{
	switch (tmf) {
	case TMR_ABORT_TASK:		return "ABORT_TASK";
	case TMR_ABORT_TASK_SET:	return "ABORT_TASK_SET";
	case TMR_CLEAR_ACA:		return "CLEAR_ACA";
	case TMR_CLEAR_TASK_SET:	return "CLEAR_TASK_SET";
	case TMR_LUN_RESET:		return "LUN_RESET";
	case TMR_TARGET_WARM_RESET:	return "TARGET_WARM_RESET";
	case TMR_TARGET_COLD_RESET:	return "TARGET_COLD_RESET";
	case TMR_UNKNOWN:		break;
	}
	return "(?)";
}