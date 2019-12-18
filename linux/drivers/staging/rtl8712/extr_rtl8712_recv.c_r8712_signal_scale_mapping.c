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
typedef  int s32 ;

/* Variables and functions */

s32 r8712_signal_scale_mapping(s32 cur_sig)
{
	s32 ret_sig;

	if (cur_sig >= 51 && cur_sig <= 100)
		ret_sig = 100;
	else if (cur_sig >= 41 && cur_sig <= 50)
		ret_sig = 80 + ((cur_sig - 40) * 2);
	else if (cur_sig >= 31 && cur_sig <= 40)
		ret_sig = 66 + (cur_sig - 30);
	else if (cur_sig >= 21 && cur_sig <= 30)
		ret_sig = 54 + (cur_sig - 20);
	else if (cur_sig >= 10 && cur_sig <= 20)
		ret_sig = 42 + (((cur_sig - 10) * 2) / 3);
	else if (cur_sig >= 5 && cur_sig <= 9)
		ret_sig = 22 + (((cur_sig - 5) * 3) / 2);
	else if (cur_sig >= 1 && cur_sig <= 4)
		ret_sig = 6 + (((cur_sig - 1) * 3) / 2);
	else
		ret_sig = cur_sig;
	return ret_sig;
}