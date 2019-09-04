#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct bios_parser {int /*<<< orphan*/  remap_device_tags; } ;
typedef  scalar_t__ USHORT ;
struct TYPE_6__ {void* usDeviceID; void* ulACPIDeviceEnum; } ;
struct TYPE_5__ {int /*<<< orphan*/  usDeviceACPIEnum; int /*<<< orphan*/  usDeviceTag; } ;
typedef  TYPE_1__ EXT_DISPLAY_PATH ;
typedef  TYPE_2__ ATOM_CONNECTOR_DEVICE_TAG ;

/* Variables and functions */
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int enum_first_device_id (scalar_t__) ; 
 int enum_next_dev_id (int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool get_patched_device_tag(
	struct bios_parser *bp,
	EXT_DISPLAY_PATH *ext_display_path,
	uint32_t device_support,
	ATOM_CONNECTOR_DEVICE_TAG *device_tag)
{
	uint32_t dev_id;
	/* Use fallback behaviour if not supported. */
	if (!bp->remap_device_tags) {
		device_tag->ulACPIDeviceEnum =
				cpu_to_le32((uint32_t) le16_to_cpu(ext_display_path->usDeviceACPIEnum));
		device_tag->usDeviceID =
				cpu_to_le16(le16_to_cpu(ext_display_path->usDeviceTag));
		return true;
	}

	/* Find the first unused in the same group. */
	dev_id = enum_first_device_id(le16_to_cpu(ext_display_path->usDeviceTag));
	while (dev_id != 0) {
		/* Assign this device ID if supported. */
		if ((device_support & dev_id) != 0) {
			device_tag->ulACPIDeviceEnum =
					cpu_to_le32((uint32_t) le16_to_cpu(ext_display_path->usDeviceACPIEnum));
			device_tag->usDeviceID = cpu_to_le16((USHORT) dev_id);
			return true;
		}

		dev_id = enum_next_dev_id(dev_id);
	}

	/* No compatible device ID found. */
	return false;
}