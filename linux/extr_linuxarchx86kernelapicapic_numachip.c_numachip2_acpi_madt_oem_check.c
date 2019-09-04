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
 int numachip_system ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int numachip2_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
{
	if ((strncmp(oem_id, "NUMASC", 6) != 0) ||
	    (strncmp(oem_table_id, "NCONECT2", 8) != 0))
		return 0;

	numachip_system = 2;

	return 1;
}