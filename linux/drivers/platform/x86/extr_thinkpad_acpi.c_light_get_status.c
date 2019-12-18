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
struct TYPE_2__ {scalar_t__ light_status; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  ec_handle ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static int light_get_status(void)
{
	int status = 0;

	if (tp_features.light_status) {
		if (!acpi_evalf(ec_handle, &status, "KBLT", "d"))
			return -EIO;
		return (!!status);
	}

	return -ENXIO;
}