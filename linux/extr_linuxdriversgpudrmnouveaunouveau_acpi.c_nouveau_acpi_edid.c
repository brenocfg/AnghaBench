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
struct drm_device {TYPE_1__* pdev; } ;
struct drm_connector {int connector_type; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int ACPI_VIDEO_DISPLAY_LCD ; 
#define  DRM_MODE_CONNECTOR_LVDS 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 int /*<<< orphan*/  EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_video_get_edid (struct acpi_device*,int,int,void**) ; 
 void* kmemdup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
nouveau_acpi_edid(struct drm_device *dev, struct drm_connector *connector)
{
	struct acpi_device *acpidev;
	acpi_handle handle;
	int type, ret;
	void *edid;

	switch (connector->connector_type) {
	case DRM_MODE_CONNECTOR_LVDS:
	case DRM_MODE_CONNECTOR_eDP:
		type = ACPI_VIDEO_DISPLAY_LCD;
		break;
	default:
		return NULL;
	}

	handle = ACPI_HANDLE(&dev->pdev->dev);
	if (!handle)
		return NULL;

	ret = acpi_bus_get_device(handle, &acpidev);
	if (ret)
		return NULL;

	ret = acpi_video_get_edid(acpidev, type, -1, &edid);
	if (ret < 0)
		return NULL;

	return kmemdup(edid, EDID_LENGTH, GFP_KERNEL);
}