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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_evalf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ec_write (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ecwr_handle ; 

__attribute__((used)) static int acpi_ec_write(int i, u8 v)
{
	if (ecwr_handle) {
		if (!acpi_evalf(ecwr_handle, NULL, NULL, "vdd", i, v))
			return 0;
	} else {
		if (ec_write(i, v) < 0)
			return 0;
	}

	return 1;
}