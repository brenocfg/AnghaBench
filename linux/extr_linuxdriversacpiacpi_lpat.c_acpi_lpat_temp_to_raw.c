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
struct acpi_lpat_conversion_table {int lpat_count; struct acpi_lpat* lpat; } ;
struct acpi_lpat {int temp; int raw; } ;

/* Variables and functions */
 int ENOENT ; 

int acpi_lpat_temp_to_raw(struct acpi_lpat_conversion_table *lpat_table,
			  int temp)
{
	int i, delta_temp, delta_raw, raw;
	struct acpi_lpat *lpat = lpat_table->lpat;

	for (i = 0; i < lpat_table->lpat_count - 1; i++) {
		if (temp >= lpat[i].temp && temp <= lpat[i+1].temp)
			break;
	}

	if (i ==  lpat_table->lpat_count - 1)
		return -ENOENT;

	delta_temp = lpat[i+1].temp - lpat[i].temp;
	delta_raw = lpat[i+1].raw - lpat[i].raw;
	raw = lpat[i].raw + (temp - lpat[i].temp) * delta_raw / delta_temp;

	return raw;
}