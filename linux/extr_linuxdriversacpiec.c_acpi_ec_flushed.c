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
struct acpi_ec {int reference_count; } ;

/* Variables and functions */

__attribute__((used)) static bool acpi_ec_flushed(struct acpi_ec *ec)
{
	return ec->reference_count == 1;
}