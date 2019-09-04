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
 int early_per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  x86_cpu_to_apicid ; 

__attribute__((used)) static int bigsmp_early_logical_apicid(int cpu)
{
	/* on bigsmp, logical apicid is the same as physical */
	return early_per_cpu(x86_cpu_to_apicid, cpu);
}