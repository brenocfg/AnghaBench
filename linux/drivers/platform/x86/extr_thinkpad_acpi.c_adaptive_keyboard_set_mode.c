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
 int EINVAL ; 
 int EIO ; 
 int LAYFLAT_MODE ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int adaptive_keyboard_set_mode(int new_mode)
{
	if (new_mode < 0 ||
		new_mode > LAYFLAT_MODE)
		return -EINVAL;

	if (!acpi_evalf(hkey_handle, NULL, "STRW", "vd", new_mode)) {
		pr_err("Cannot set adaptive keyboard mode\n");
		return -EIO;
	}

	return 0;
}