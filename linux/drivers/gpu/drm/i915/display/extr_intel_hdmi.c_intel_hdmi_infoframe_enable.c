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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 unsigned int* infoframe_type_to_idx ; 

u32 intel_hdmi_infoframe_enable(unsigned int type)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(infoframe_type_to_idx); i++) {
		if (infoframe_type_to_idx[i] == type)
			return BIT(i);
	}

	return 0;
}