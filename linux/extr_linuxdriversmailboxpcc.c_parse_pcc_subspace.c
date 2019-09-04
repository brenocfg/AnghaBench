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
struct acpi_subtable_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct acpi_pcct_subspace {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ ACPI_PCCT_TYPE_RESERVED ; 
 int EINVAL ; 

__attribute__((used)) static int parse_pcc_subspace(struct acpi_subtable_header *header,
		const unsigned long end)
{
	struct acpi_pcct_subspace *ss = (struct acpi_pcct_subspace *) header;

	if (ss->header.type < ACPI_PCCT_TYPE_RESERVED)
		return 0;

	return -EINVAL;
}