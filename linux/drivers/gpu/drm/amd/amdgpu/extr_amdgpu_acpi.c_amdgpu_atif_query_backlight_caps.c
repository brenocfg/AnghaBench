#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  size_t u16 ;
struct atif_qbtc_output {int /*<<< orphan*/  max_input_signal; int /*<<< orphan*/  min_input_signal; } ;
struct atif_qbtc_arguments {int size; int /*<<< orphan*/  requested_display; } ;
struct TYPE_4__ {int caps_valid; int /*<<< orphan*/  max_input_signal; int /*<<< orphan*/  min_input_signal; } ;
struct amdgpu_atif {TYPE_2__ backlight_caps; } ;
struct acpi_buffer {int length; void* pointer; } ;
typedef  int /*<<< orphan*/  characteristics ;
typedef  int /*<<< orphan*/  arguments ;

/* Variables and functions */
 int /*<<< orphan*/  ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS ; 
 int /*<<< orphan*/  ATIF_QBTC_REQUEST_LCD1 ; 
 int EINVAL ; 
 int EIO ; 
 union acpi_object* amdgpu_atif_call (struct amdgpu_atif*,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atif_qbtc_output*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atif_qbtc_output*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 

__attribute__((used)) static int amdgpu_atif_query_backlight_caps(struct amdgpu_atif *atif)
{
	union acpi_object *info;
	struct atif_qbtc_output characteristics;
	struct atif_qbtc_arguments arguments;
	struct acpi_buffer params;
	size_t size;
	int err = 0;

	arguments.size = sizeof(arguments);
	arguments.requested_display = ATIF_QBTC_REQUEST_LCD1;

	params.length = sizeof(arguments);
	params.pointer = (void *)&arguments;

	info = amdgpu_atif_call(atif,
		ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS,
		&params);
	if (!info) {
		err = -EIO;
		goto out;
	}

	size = *(u16 *) info->buffer.pointer;
	if (size < 10) {
		err = -EINVAL;
		goto out;
	}

	memset(&characteristics, 0, sizeof(characteristics));
	size = min(sizeof(characteristics), size);
	memcpy(&characteristics, info->buffer.pointer, size);

	atif->backlight_caps.caps_valid = true;
	atif->backlight_caps.min_input_signal =
			characteristics.min_input_signal;
	atif->backlight_caps.max_input_signal =
			characteristics.max_input_signal;
out:
	kfree(info);
	return err;
}