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
 int /*<<< orphan*/  CIF_DEDICATED_CPU ; 
 int /*<<< orphan*/  clear_cpu_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ topology_cpu_dedicated (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __arch_update_dedicated_flag(void *arg)
{
	if (topology_cpu_dedicated(smp_processor_id()))
		set_cpu_flag(CIF_DEDICATED_CPU);
	else
		clear_cpu_flag(CIF_DEDICATED_CPU);
}