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
struct acpi_table_wdat {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool acpi_watchdog_uses_rtc(const struct acpi_table_wdat *wdat)
{
	return false;
}