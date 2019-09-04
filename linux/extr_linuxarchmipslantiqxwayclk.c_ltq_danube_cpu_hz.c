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
 unsigned long CLOCK_333M ; 
 unsigned long DDR_HZ ; 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 

unsigned long ltq_danube_cpu_hz(void)
{
	switch (ltq_cgu_r32(CGU_SYS) & 0xc) {
	case 0:
		return CLOCK_333M;
	case 4:
		return DDR_HZ;
	case 8:
		return DDR_HZ << 1;
	default:
		return DDR_HZ >> 1;
	}
}