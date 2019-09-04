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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ TMR_CVWR (int) ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ mmp_timer_base ; 

__attribute__((used)) static inline uint32_t timer_read(void)
{
	int delay = 100;

	__raw_writel(1, mmp_timer_base + TMR_CVWR(1));

	while (delay--)
		cpu_relax();

	return __raw_readl(mmp_timer_base + TMR_CVWR(1));
}