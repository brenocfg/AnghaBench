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
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2_cpuid_addr ; 

__attribute__((used)) static unsigned int j2_smp_processor_id(void)
{
	return __raw_readl(sh2_cpuid_addr);
}