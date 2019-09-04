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
struct irq_fwspec {int dummy; } ;
struct acpi_irq_parse_one_ctx {unsigned int member_1; unsigned long* member_2; int rc; struct irq_fwspec* member_3; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_irq_parse_one_cb ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_irq_parse_one_ctx*) ; 

__attribute__((used)) static int acpi_irq_parse_one(acpi_handle handle, unsigned int index,
			      struct irq_fwspec *fwspec, unsigned long *flags)
{
	struct acpi_irq_parse_one_ctx ctx = { -EINVAL, index, flags, fwspec };

	acpi_walk_resources(handle, METHOD_NAME__CRS, acpi_irq_parse_one_cb, &ctx);
	return ctx.rc;
}