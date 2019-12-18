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
struct atpx_mux {int size; int /*<<< orphan*/  mux; } ;
struct TYPE_2__ {scalar_t__ switch_start; } ;
struct amdgpu_atpx {int /*<<< orphan*/  handle; TYPE_1__ functions; } ;
struct acpi_buffer {int length; struct atpx_mux* pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION ; 
 int EIO ; 
 union acpi_object* amdgpu_atpx_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static int amdgpu_atpx_switch_start(struct amdgpu_atpx *atpx, u16 mux_id)
{
	struct acpi_buffer params;
	union acpi_object *info;
	struct atpx_mux input;

	if (atpx->functions.switch_start) {
		input.size = 4;
		input.mux = mux_id;
		params.length = input.size;
		params.pointer = &input;
		info = amdgpu_atpx_call(atpx->handle,
					ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION,
					&params);
		if (!info)
			return -EIO;
		kfree(info);
	}
	return 0;
}