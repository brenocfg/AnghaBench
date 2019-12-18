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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  hkey_handle ; 

__attribute__((used)) static int hotkey_status_get(int *status)
{
	if (!acpi_evalf(hkey_handle, status, "DHKC", "d"))
		return -EIO;

	return 0;
}