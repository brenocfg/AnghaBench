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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool acpi_dev_resource_len_valid(u64 start, u64 end, u64 len, bool io)
{
	u64 reslen = end - start + 1;

	/*
	 * CHECKME: len might be required to check versus a minimum
	 * length as well. 1 for io is fine, but for memory it does
	 * not make any sense at all.
	 * Note: some BIOSes report incorrect length for ACPI address space
	 * descriptor, so remove check of 'reslen == len' to avoid regression.
	 */
	if (len && reslen && start <= end)
		return true;

	pr_debug("ACPI: invalid or unassigned resource %s [%016llx - %016llx] length [%016llx]\n",
		io ? "io" : "mem", start, end, len);

	return false;
}