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
 int EINVAL ; 
 int LM3532_NUM_IMP_VALS ; 
 int* als_imp_table ; 

__attribute__((used)) static int lm3532_get_als_imp_index(int als_imped)
{
	int i;

	if (als_imped > als_imp_table[1])
		return 0;

	if (als_imped < als_imp_table[LM3532_NUM_IMP_VALS - 1])
		return LM3532_NUM_IMP_VALS - 1;

	for (i = 1; i < LM3532_NUM_IMP_VALS; i++) {
		if (als_imped == als_imp_table[i])
			return i;

		/* Find an approximate index by looking up the table */
		if (als_imped < als_imp_table[i - 1] &&
		    als_imped > als_imp_table[i]) {
			if (als_imped - als_imp_table[i - 1] <
			    als_imp_table[i] - als_imped)
				return i + 1;
			else
				return i;
		}
	}

	return -EINVAL;
}