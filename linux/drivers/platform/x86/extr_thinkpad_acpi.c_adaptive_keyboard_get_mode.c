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
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int adaptive_keyboard_get_mode(void)
{
	int mode = 0;

	if (!acpi_evalf(hkey_handle, &mode, "GTRW", "dd", 0)) {
		pr_err("Cannot read adaptive keyboard mode\n");
		return -EIO;
	}

	return mode;
}