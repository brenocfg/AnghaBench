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

/* Variables and functions */
#define  SCU_TASK_OPEN_REJECT_BAD_DESTINATION 133 
#define  SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1 132 
#define  SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2 131 
#define  SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3 130 
#define  SCU_TASK_OPEN_REJECT_WRONG_DESTINATION 129 
#define  SCU_TASK_OPEN_REJECT_ZONE_VIOLATION 128 

__attribute__((used)) static int sci_request_smp_completion_status_is_tx_suspend(
	unsigned int completion_status)
{
	switch (completion_status) {
	case SCU_TASK_OPEN_REJECT_WRONG_DESTINATION:
	case SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1:
	case SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2:
	case SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3:
	case SCU_TASK_OPEN_REJECT_BAD_DESTINATION:
	case SCU_TASK_OPEN_REJECT_ZONE_VIOLATION:
		return 1;
	}
	return 0;
}