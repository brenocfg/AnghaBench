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
struct TYPE_2__ {scalar_t__ flags; } ;
struct resource_win {TYPE_1__ res; } ;
struct acpi_resource_address64 {int /*<<< orphan*/  address; } ;
struct acpi_resource_address {int dummy; } ;
struct acpi_resource {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int acpi_decode_space (struct resource_win*,struct acpi_resource_address*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_resource_to_address64 (struct acpi_resource*,struct acpi_resource_address64*) ; 

bool acpi_dev_resource_address_space(struct acpi_resource *ares,
				     struct resource_win *win)
{
	struct acpi_resource_address64 addr;

	win->res.flags = 0;
	if (ACPI_FAILURE(acpi_resource_to_address64(ares, &addr)))
		return false;

	return acpi_decode_space(win, (struct acpi_resource_address *)&addr,
				 &addr.address);
}