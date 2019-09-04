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
struct acpi_gpe_event_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TO_POINTER (int) ; 
 struct acpi_gpe_event_info* acpi_ev_get_gpe_event_info (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_ev_gpe_dispatch (int /*<<< orphan*/ *,struct acpi_gpe_event_info*,int) ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void acpi_db_generate_gpe(char *gpe_arg, char *block_arg)
{
	u32 block_number = 0;
	u32 gpe_number;
	struct acpi_gpe_event_info *gpe_event_info;

	gpe_number = strtoul(gpe_arg, NULL, 0);

	/*
	 * If no block arg, or block arg == 0 or 1, use the FADT-defined
	 * GPE blocks.
	 */
	if (block_arg) {
		block_number = strtoul(block_arg, NULL, 0);
		if (block_number == 1) {
			block_number = 0;
		}
	}

	gpe_event_info =
	    acpi_ev_get_gpe_event_info(ACPI_TO_POINTER(block_number),
				       gpe_number);
	if (!gpe_event_info) {
		acpi_os_printf("Invalid GPE\n");
		return;
	}

	(void)acpi_ev_gpe_dispatch(NULL, gpe_event_info, gpe_number);
}