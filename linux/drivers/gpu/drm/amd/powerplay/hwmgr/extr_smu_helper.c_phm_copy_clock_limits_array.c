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
typedef  int uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int const) ; 

int phm_copy_clock_limits_array(
	struct pp_hwmgr *hwmgr,
	uint32_t **pptable_info_array,
	const uint32_t *pptable_array,
	uint32_t power_saving_clock_count)
{
	uint32_t array_size, i;
	uint32_t *table;

	array_size = sizeof(uint32_t) * power_saving_clock_count;
	table = kzalloc(array_size, GFP_KERNEL);
	if (NULL == table)
		return -ENOMEM;

	for (i = 0; i < power_saving_clock_count; i++)
		table[i] = le32_to_cpu(pptable_array[i]);

	*pptable_info_array = table;

	return 0;
}