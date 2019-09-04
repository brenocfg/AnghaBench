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
typedef  int u32 ;

/* Variables and functions */

void i40iw_get_wqe_shift(u32 sge, u32 inline_data, u8 *shift)
{
	*shift = 0;
	if (sge > 1 || inline_data > 16)
		*shift = (sge < 4 && inline_data <= 48) ? 1 : 2;
}