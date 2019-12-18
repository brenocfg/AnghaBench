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
struct pch_thermal_device {int psv_trip_id; } ;

/* Variables and functions */

__attribute__((used)) static void pch_wpt_add_acpi_psv_trip(struct pch_thermal_device *ptd,
				      int *nr_trips)
{
	ptd->psv_trip_id = -1;

}