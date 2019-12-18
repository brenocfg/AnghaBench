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
struct asus_laptop {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENODEV ; 
 char* METHOD_GPS_OFF ; 
 char* METHOD_GPS_ON ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int asus_gps_switch(struct asus_laptop *asus, int status)
{
	const char *meth = status ? METHOD_GPS_ON : METHOD_GPS_OFF;

	if (write_acpi_int(asus->handle, meth, 0x02))
		return -ENODEV;
	return 0;
}