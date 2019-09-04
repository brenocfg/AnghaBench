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
 int exynos_cpu_do_idle () ; 
 int /*<<< orphan*/  flush_cache_all () ; 

__attribute__((used)) static int exynos3250_cpu_suspend(unsigned long arg)
{
	flush_cache_all();
	return exynos_cpu_do_idle();
}