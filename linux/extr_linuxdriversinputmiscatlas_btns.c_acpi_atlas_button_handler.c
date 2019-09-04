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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_WRITE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/ * atlas_keymap ; 
 int /*<<< orphan*/  input_dev ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,unsigned long,scalar_t__) ; 

__attribute__((used)) static acpi_status acpi_atlas_button_handler(u32 function,
		      acpi_physical_address address,
		      u32 bit_width, u64 *value,
		      void *handler_context, void *region_context)
{
	acpi_status status;

	if (function == ACPI_WRITE) {
		int code = address & 0x0f;
		int key_down = !(address & 0x10);

		input_event(input_dev, EV_MSC, MSC_SCAN, code);
		input_report_key(input_dev, atlas_keymap[code], key_down);
		input_sync(input_dev);

		status = AE_OK;
	} else {
		pr_warn("shrugged on unexpected function: function=%x,address=%lx,value=%x\n",
			function, (unsigned long)address, (u32)*value);
		status = AE_BAD_PARAMETER;
	}

	return status;
}