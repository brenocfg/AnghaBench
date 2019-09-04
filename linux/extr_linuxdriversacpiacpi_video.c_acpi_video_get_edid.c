#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* pointer; } ;
union acpi_object {scalar_t__ type; TYPE_4__ buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  lcd; int /*<<< orphan*/  dvi; int /*<<< orphan*/  tvout; int /*<<< orphan*/  crt; } ;
struct TYPE_6__ {int /*<<< orphan*/  _DDC; } ;
struct acpi_video_device {int device_id; TYPE_3__ flags; TYPE_2__ cap; } ;
struct acpi_video_bus {int attached_count; TYPE_1__* attached_array; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_5__ {struct acpi_video_device* bind_info; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
#define  ACPI_VIDEO_DISPLAY_CRT 131 
#define  ACPI_VIDEO_DISPLAY_DVI 130 
#define  ACPI_VIDEO_DISPLAY_LCD 129 
#define  ACPI_VIDEO_DISPLAY_TV 128 
 int EINVAL ; 
 int ENODEV ; 
 struct acpi_video_bus* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_video_device_EDID (struct acpi_video_device*,union acpi_object**,int) ; 

int acpi_video_get_edid(struct acpi_device *device, int type, int device_id,
			void **edid)
{
	struct acpi_video_bus *video;
	struct acpi_video_device *video_device;
	union acpi_object *buffer = NULL;
	acpi_status status;
	int i, length;

	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	video = acpi_driver_data(device);

	for (i = 0; i < video->attached_count; i++) {
		video_device = video->attached_array[i].bind_info;
		length = 256;

		if (!video_device)
			continue;

		if (!video_device->cap._DDC)
			continue;

		if (type) {
			switch (type) {
			case ACPI_VIDEO_DISPLAY_CRT:
				if (!video_device->flags.crt)
					continue;
				break;
			case ACPI_VIDEO_DISPLAY_TV:
				if (!video_device->flags.tvout)
					continue;
				break;
			case ACPI_VIDEO_DISPLAY_DVI:
				if (!video_device->flags.dvi)
					continue;
				break;
			case ACPI_VIDEO_DISPLAY_LCD:
				if (!video_device->flags.lcd)
					continue;
				break;
			}
		} else if (video_device->device_id != device_id) {
			continue;
		}

		status = acpi_video_device_EDID(video_device, &buffer, length);

		if (ACPI_FAILURE(status) || !buffer ||
		    buffer->type != ACPI_TYPE_BUFFER) {
			length = 128;
			status = acpi_video_device_EDID(video_device, &buffer,
							length);
			if (ACPI_FAILURE(status) || !buffer ||
			    buffer->type != ACPI_TYPE_BUFFER) {
				continue;
			}
		}

		*edid = buffer->buffer.pointer;
		return length;
	}

	return -ENODEV;
}