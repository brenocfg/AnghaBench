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
struct acpi_buffer {int length; void* pointer; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PROCESSOR_AGGREGATOR_NOTIFY ; 
 int /*<<< orphan*/  acpi_evaluate_ost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_pad_idle_cpus (int) ; 
 int /*<<< orphan*/  acpi_pad_idle_cpus_num () ; 
 int acpi_pad_pur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isolated_cpus_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_pad_handle_notify(acpi_handle handle)
{
	int num_cpus;
	uint32_t idle_cpus;
	struct acpi_buffer param = {
		.length = 4,
		.pointer = (void *)&idle_cpus,
	};

	mutex_lock(&isolated_cpus_lock);
	num_cpus = acpi_pad_pur(handle);
	if (num_cpus < 0) {
		mutex_unlock(&isolated_cpus_lock);
		return;
	}
	acpi_pad_idle_cpus(num_cpus);
	idle_cpus = acpi_pad_idle_cpus_num();
	acpi_evaluate_ost(handle, ACPI_PROCESSOR_AGGREGATOR_NOTIFY, 0, &param);
	mutex_unlock(&isolated_cpus_lock);
}