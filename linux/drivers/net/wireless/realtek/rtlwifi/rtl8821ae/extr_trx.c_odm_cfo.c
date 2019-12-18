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
typedef  int u16 ;
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static u16 odm_cfo(s8 value)
{
	int ret_val;

	if (value < 0) {
		ret_val = 0 - value;
		ret_val = (ret_val << 1) + (ret_val >> 1);
		/* set bit12 as 1 for negative cfo */
		ret_val = ret_val | BIT(12);
	} else {
		ret_val = value;
		ret_val = (ret_val << 1) + (ret_val >> 1);
	}
	return ret_val;
}