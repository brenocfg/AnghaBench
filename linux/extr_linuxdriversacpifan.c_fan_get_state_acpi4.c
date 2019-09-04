#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; TYPE_2__* elements; } ;
union acpi_object {scalar_t__ type; TYPE_3__ package; } ;
struct TYPE_9__ {scalar_t__ fine_grain_ctrl; } ;
struct acpi_fan {int fps_count; TYPE_5__* fps; TYPE_4__ fif; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int acpi_status ;
struct TYPE_10__ {int control; } ;
struct TYPE_6__ {int value; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EINVAL ; 
 struct acpi_fan* acpi_driver_data (struct acpi_device*) ; 
 int acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static int fan_get_state_acpi4(struct acpi_device *device, unsigned long *state)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_fan *fan = acpi_driver_data(device);
	union acpi_object *obj;
	acpi_status status;
	int control, i;

	status = acpi_evaluate_object(device->handle, "_FST", NULL, &buffer);
	if (ACPI_FAILURE(status)) {
		dev_err(&device->dev, "Get fan state failed\n");
		return status;
	}

	obj = buffer.pointer;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE ||
	    obj->package.count != 3 ||
	    obj->package.elements[1].type != ACPI_TYPE_INTEGER) {
		dev_err(&device->dev, "Invalid _FST data\n");
		status = -EINVAL;
		goto err;
	}

	control = obj->package.elements[1].integer.value;
	for (i = 0; i < fan->fps_count; i++) {
		/*
		 * When Fine Grain Control is set, return the state
		 * corresponding to maximum fan->fps[i].control
		 * value compared to the current speed. Here the
		 * fan->fps[] is sorted array with increasing speed.
		 */
		if (fan->fif.fine_grain_ctrl && control < fan->fps[i].control) {
			i = (i > 0) ? i - 1 : 0;
			break;
		} else if (control == fan->fps[i].control) {
			break;
		}
	}
	if (i == fan->fps_count) {
		dev_dbg(&device->dev, "Invalid control value returned\n");
		status = -EINVAL;
		goto err;
	}

	*state = i;

err:
	kfree(obj);
	return status;
}