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
 int /*<<< orphan*/  CGU_SYS ; 
 unsigned long CLOCK_250M ; 
 unsigned long CLOCK_400M ; 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 

unsigned long ltq_ar10_pp32_hz(void)
{
	unsigned int clksys = (ltq_cgu_r32(CGU_SYS) >> 16) & 0x7;
	unsigned long clk;

	switch (clksys) {
	case 1:
		clk = CLOCK_250M;
		break;
	case 4:
		clk = CLOCK_400M;
		break;
	default:
		clk = CLOCK_250M;
		break;
	}

	return clk;
}