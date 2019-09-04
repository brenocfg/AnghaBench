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
typedef  union acpi_object {int dummy; } acpi_object ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ disp_mux_cntl; } ;
struct radeon_atpx {int /*<<< orphan*/  handle; TYPE_1__ functions; } ;
struct atpx_mux {int size; int /*<<< orphan*/  mux; } ;
struct acpi_buffer {int length; struct atpx_mux* pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATPX_FUNCTION_DISPLAY_MUX_CONTROL ; 
 int EIO ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 union acpi_object* radeon_atpx_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 

__attribute__((used)) static int radeon_atpx_switch_disp_mux(struct radeon_atpx *atpx, u16 mux_id)
{
	struct acpi_buffer params;
	union acpi_object *info;
	struct atpx_mux input;

	if (atpx->functions.disp_mux_cntl) {
		input.size = 4;
		input.mux = mux_id;
		params.length = input.size;
		params.pointer = &input;
		info = radeon_atpx_call(atpx->handle,
					ATPX_FUNCTION_DISPLAY_MUX_CONTROL,
					&params);
		if (!info)
			return -EIO;
		kfree(info);
	}
	return 0;
}