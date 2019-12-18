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
 int LM3532_NUM_AVG_VALS ; 
 int* als_avrg_table ; 
 int lm3532_get_index (int*,int,int) ; 

__attribute__((used)) static int lm3532_get_als_avg_index(int avg_time)
{
	if (avg_time <= als_avrg_table[0])
		return 0;

	if (avg_time > als_avrg_table[LM3532_NUM_AVG_VALS - 1])
		return LM3532_NUM_AVG_VALS - 1;

	return lm3532_get_index(&als_avrg_table[0], LM3532_NUM_AVG_VALS,
				avg_time);
}