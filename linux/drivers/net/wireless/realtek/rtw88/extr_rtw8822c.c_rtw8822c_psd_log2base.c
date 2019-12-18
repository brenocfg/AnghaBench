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
typedef  int u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int __fls (int) ; 

__attribute__((used)) static u32 rtw8822c_psd_log2base(u32 val)
{
	u32 tmp, val_integerd_b, tindex;
	u32 result, val_fractiond_b;
	u32 table_fraction[21] = {0, 432, 332, 274, 232, 200, 174,
				  151, 132, 115, 100, 86, 74, 62, 51,
				  42, 32, 23, 15, 7, 0};

	if (val == 0)
		return 0;

	val_integerd_b = __fls(val) + 1;

	tmp = (val * 100) / (1 << val_integerd_b);
	tindex = tmp / 5;

	if (tindex >= ARRAY_SIZE(table_fraction))
		tindex = ARRAY_SIZE(table_fraction) - 1;

	val_fractiond_b = table_fraction[tindex];

	result = val_integerd_b * 100 - val_fractiond_b;

	return result;
}