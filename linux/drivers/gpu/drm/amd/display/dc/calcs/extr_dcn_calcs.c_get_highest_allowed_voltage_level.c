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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ASICREV_IS_DALI (int /*<<< orphan*/ ) ; 

unsigned int get_highest_allowed_voltage_level(uint32_t hw_internal_rev)
{
	/* for dali, the highest voltage level we want is 0 */
	if (ASICREV_IS_DALI(hw_internal_rev))
		return 0;

	/* we are ok with all levels */
	return 4;
}