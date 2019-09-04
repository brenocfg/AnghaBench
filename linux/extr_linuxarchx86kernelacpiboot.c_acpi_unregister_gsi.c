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

/* Variables and functions */
 int /*<<< orphan*/  __acpi_unregister_gsi (int /*<<< orphan*/ ) ; 

void acpi_unregister_gsi(u32 gsi)
{
	if (__acpi_unregister_gsi)
		__acpi_unregister_gsi(gsi);
}