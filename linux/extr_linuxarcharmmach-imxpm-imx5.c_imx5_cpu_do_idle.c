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
 int /*<<< orphan*/  cpu_do_idle () ; 
 scalar_t__ likely (int) ; 
 int tzic_enable_wake () ; 

__attribute__((used)) static inline int imx5_cpu_do_idle(void)
{
	int ret = tzic_enable_wake();

	if (likely(!ret))
		cpu_do_idle();

	return ret;
}