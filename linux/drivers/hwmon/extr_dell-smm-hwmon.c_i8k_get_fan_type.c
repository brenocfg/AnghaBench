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
#define  INT_MIN 128 
 int _i8k_get_fan_type (int) ; 

__attribute__((used)) static int i8k_get_fan_type(int fan)
{
	/* I8K_SMM_GET_FAN_TYPE SMM call is expensive, so cache values */
	static int types[3] = { INT_MIN, INT_MIN, INT_MIN };

	if (types[fan] == INT_MIN)
		types[fan] = _i8k_get_fan_type(fan);

	return types[fan];
}