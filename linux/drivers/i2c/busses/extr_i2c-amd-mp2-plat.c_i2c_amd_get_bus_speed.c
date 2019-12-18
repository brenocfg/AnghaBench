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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  enum speed_enum { ____Placeholder_speed_enum } speed_enum ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int i2c_acpi_find_bus_speed (int /*<<< orphan*/ *) ; 
 int speed1000k ; 
 int speed100k ; 
 int speed1400k ; 
 int speed3400k ; 
 int speed400k ; 

__attribute__((used)) static enum speed_enum i2c_amd_get_bus_speed(struct platform_device *pdev)
{
	u32 acpi_speed;
	int i;
	static const u32 supported_speeds[] = {
		0, 100000, 400000, 1000000, 1400000, 3400000
	};

	acpi_speed = i2c_acpi_find_bus_speed(&pdev->dev);
	/* round down to the lowest standard speed */
	for (i = 1; i < ARRAY_SIZE(supported_speeds); i++) {
		if (acpi_speed < supported_speeds[i])
			break;
	}
	acpi_speed = supported_speeds[i - 1];

	switch (acpi_speed) {
	case 100000:
		return speed100k;
	case 400000:
		return speed400k;
	case 1000000:
		return speed1000k;
	case 1400000:
		return speed1400k;
	case 3400000:
		return speed3400k;
	default:
		return speed400k;
	}
}