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
typedef  scalar_t__ u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ NR_CPUS ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int riscv_of_processor_hart(struct device_node *node)
{
	const char *isa, *status;
	u32 hart;

	if (!of_device_is_compatible(node, "riscv")) {
		pr_warn("Found incompatible CPU\n");
		return -(ENODEV);
	}

	if (of_property_read_u32(node, "reg", &hart)) {
		pr_warn("Found CPU without hart ID\n");
		return -(ENODEV);
	}
	if (hart >= NR_CPUS) {
		pr_info("Found hart ID %d, which is above NR_CPUs.  Disabling this hart\n", hart);
		return -(ENODEV);
	}

	if (of_property_read_string(node, "status", &status)) {
		pr_warn("CPU with hartid=%d has no \"status\" property\n", hart);
		return -(ENODEV);
	}
	if (strcmp(status, "okay")) {
		pr_info("CPU with hartid=%d has a non-okay status of \"%s\"\n", hart, status);
		return -(ENODEV);
	}

	if (of_property_read_string(node, "riscv,isa", &isa)) {
		pr_warn("CPU with hartid=%d has no \"riscv,isa\" property\n", hart);
		return -(ENODEV);
	}
	if (isa[0] != 'r' || isa[1] != 'v') {
		pr_warn("CPU with hartid=%d has an invalid ISA of \"%s\"\n", hart, isa);
		return -(ENODEV);
	}

	return hart;
}