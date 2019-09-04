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
typedef  int /*<<< orphan*/  u32 ;
struct cpumask {int dummy; } ;
struct acpi_cpufreq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_empty (struct cpumask const*) ; 
 int /*<<< orphan*/  drv_read (struct acpi_cpufreq_data*,struct cpumask const*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_cur_val(const struct cpumask *mask, struct acpi_cpufreq_data *data)
{
	u32 val;

	if (unlikely(cpumask_empty(mask)))
		return 0;

	val = drv_read(data, mask);

	pr_debug("get_cur_val = %u\n", val);

	return val;
}