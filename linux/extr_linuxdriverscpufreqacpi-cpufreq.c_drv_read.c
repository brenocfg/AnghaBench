#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  read; } ;
struct drv_cmd {int /*<<< orphan*/  val; TYPE_1__ func; int /*<<< orphan*/ * reg; } ;
struct cpumask {int dummy; } ;
struct acpi_processor_performance {int /*<<< orphan*/  control_register; } ;
struct acpi_cpufreq_data {int /*<<< orphan*/  cpu_freq_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  do_drv_read ; 
 int smp_call_function_any (struct cpumask const*,int /*<<< orphan*/ ,struct drv_cmd*,int) ; 
 struct acpi_processor_performance* to_perf_data (struct acpi_cpufreq_data*) ; 

__attribute__((used)) static u32 drv_read(struct acpi_cpufreq_data *data, const struct cpumask *mask)
{
	struct acpi_processor_performance *perf = to_perf_data(data);
	struct drv_cmd cmd = {
		.reg = &perf->control_register,
		.func.read = data->cpu_freq_read,
	};
	int err;

	err = smp_call_function_any(mask, do_drv_read, &cmd, 1);
	WARN_ON_ONCE(err);	/* smp_call_function_any() was buggy? */
	return cmd.val;
}