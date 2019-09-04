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
 int /*<<< orphan*/  BUG () ; 
#define  SAFARI_CFG_DIV_1 130 
#define  SAFARI_CFG_DIV_2 129 
#define  SAFARI_CFG_DIV_32 128 
 unsigned long SAFARI_CFG_DIV_MASK ; 
 int sparc64_get_clock_tick (unsigned int) ; 

__attribute__((used)) static unsigned long get_current_freq(unsigned int cpu, unsigned long safari_cfg)
{
	unsigned long clock_tick = sparc64_get_clock_tick(cpu) / 1000;
	unsigned long ret;

	switch (safari_cfg & SAFARI_CFG_DIV_MASK) {
	case SAFARI_CFG_DIV_1:
		ret = clock_tick / 1;
		break;
	case SAFARI_CFG_DIV_2:
		ret = clock_tick / 2;
		break;
	case SAFARI_CFG_DIV_32:
		ret = clock_tick / 32;
		break;
	default:
		BUG();
	}

	return ret;
}