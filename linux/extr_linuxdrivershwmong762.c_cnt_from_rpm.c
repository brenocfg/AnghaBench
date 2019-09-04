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
 unsigned char DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long ULONG_MAX ; 
 unsigned long clamp_val (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline unsigned char cnt_from_rpm(unsigned long rpm, u32 clk_freq, u16 p,
					 u8 clk_div, u8 gear_mult)
{
	unsigned long f1 = clk_freq * 30 * gear_mult;
	unsigned long f2 = p * clk_div;

	if (!rpm)	/* to stop the fan, set cnt to 255 */
		return 0xff;

	rpm = clamp_val(rpm, f1 / (255 * f2), ULONG_MAX / f2);
	return DIV_ROUND_CLOSEST(f1, rpm * f2);
}