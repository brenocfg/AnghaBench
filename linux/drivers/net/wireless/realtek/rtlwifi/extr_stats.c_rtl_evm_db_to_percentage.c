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
typedef  int s8 ;

/* Variables and functions */
 int clamp (int,int /*<<< orphan*/ ,int) ; 

u8 rtl_evm_db_to_percentage(s8 value)
{
	s8 ret_val = clamp(-value, 0, 33) * 3;

	if (ret_val == 99)
		ret_val = 100;

	return ret_val;
}