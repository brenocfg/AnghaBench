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
 long __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_boot_vector_addr () ; 
 int /*<<< orphan*/  exynos_boot_vector_flag () ; 
 int /*<<< orphan*/  exynos_cpu_resume ; 
 int /*<<< orphan*/  writel_relaxed (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_cpu_set_boot_vector(long flags)
{
	writel_relaxed(__pa_symbol(exynos_cpu_resume),
		       exynos_boot_vector_addr());
	writel_relaxed(flags, exynos_boot_vector_flag());
}