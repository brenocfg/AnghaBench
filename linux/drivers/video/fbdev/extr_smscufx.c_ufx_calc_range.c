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

__attribute__((used)) static u32 ufx_calc_range(u32 ref_freq)
{
	if (ref_freq >= 88000000)
		return 7;

	if (ref_freq >= 54000000)
		return 6;

	if (ref_freq >= 34000000)
		return 5;

	if (ref_freq >= 21000000)
		return 4;

	if (ref_freq >= 13000000)
		return 3;

	if (ref_freq >= 8000000)
		return 2;

	return 1;
}