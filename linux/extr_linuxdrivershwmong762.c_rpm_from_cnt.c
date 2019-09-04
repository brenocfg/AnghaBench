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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int rpm_from_cnt(u8 cnt, u32 clk_freq, u16 p,
					u8 clk_div, u8 gear_mult)
{
	if (cnt == 0xff)  /* setting cnt to 255 stops the fan */
		return 0;

	return (clk_freq * 30 * gear_mult) / ((cnt ? cnt : 1) * p * clk_div);
}