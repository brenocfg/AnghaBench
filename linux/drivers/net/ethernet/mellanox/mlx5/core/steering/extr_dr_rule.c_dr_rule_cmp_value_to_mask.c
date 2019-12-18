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
typedef  int u8 ;
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static bool dr_rule_cmp_value_to_mask(u8 *mask, u8 *value,
				      u32 s_idx, u32 e_idx)
{
	u32 i;

	for (i = s_idx; i < e_idx; i++) {
		if (value[i] & ~mask[i]) {
			pr_info("Rule parameters contains a value not specified by mask\n");
			return false;
		}
	}
	return true;
}