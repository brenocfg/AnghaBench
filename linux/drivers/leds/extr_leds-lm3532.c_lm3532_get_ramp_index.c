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
 int LM3532_NUM_RAMP_VALS ; 
 int lm3532_get_index (int*,int,int) ; 
 int* ramp_table ; 

__attribute__((used)) static int lm3532_get_ramp_index(int ramp_time)
{
	if (ramp_time <= ramp_table[0])
		return 0;

	if (ramp_time > ramp_table[LM3532_NUM_RAMP_VALS - 1])
		return LM3532_NUM_RAMP_VALS - 1;

	return lm3532_get_index(&ramp_table[0], LM3532_NUM_RAMP_VALS,
				ramp_time);
}