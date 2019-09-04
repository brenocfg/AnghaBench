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
 scalar_t__ ACPI_OSI_WIN_8 ; 
 scalar_t__ acpi_gbl_osi_data ; 

bool acpi_osi_is_win8(void)
{
	return acpi_gbl_osi_data >= ACPI_OSI_WIN_8;
}