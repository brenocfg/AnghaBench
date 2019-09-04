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
typedef  scalar_t__ uint32_t ;
struct pp_hwmgr {scalar_t__ usec_timeout; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIME ; 
 scalar_t__ cgs_read_register (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

int phm_wait_for_register_unequal(struct pp_hwmgr *hwmgr,
					uint32_t index,
					uint32_t value, uint32_t mask)
{
	uint32_t i;
	uint32_t cur_value;

	if (hwmgr == NULL || hwmgr->device == NULL)
		return -EINVAL;

	for (i = 0; i < hwmgr->usec_timeout; i++) {
		cur_value = cgs_read_register(hwmgr->device,
									index);
		if ((cur_value & mask) != (value & mask))
			break;
		udelay(1);
	}

	/* timeout means wrong logic */
	if (i == hwmgr->usec_timeout)
		return -ETIME;
	return 0;
}