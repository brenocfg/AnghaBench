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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct radeon_mode_info {struct atom_context* atom_context; } ;
struct radeon_device {int flags; struct radeon_mode_info mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct atom_context {int bios; } ;
struct TYPE_2__ {int ucSupportedLink; } ;
typedef  TYPE_1__ ATOM_XTMDS_INFO ;

/* Variables and functions */
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_XTMDS_SUPPORTED_DUALLINK ; 
 int CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D ; 
 int CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I ; 
 int CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D ; 
 int CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I ; 
 int /*<<< orphan*/  DATA ; 
 int DRM_MODE_CONNECTOR_DVID ; 
 int DRM_MODE_CONNECTOR_DVII ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  XTMDS_Info ; 
 scalar_t__ atom_parse_data_header (struct atom_context*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int* supported_devices_connector_object_id_convert ; 

__attribute__((used)) static uint16_t atombios_get_connector_object_id(struct drm_device *dev,
						 int connector_type,
						 uint16_t devices)
{
	struct radeon_device *rdev = dev->dev_private;

	if (rdev->flags & RADEON_IS_IGP) {
		return supported_devices_connector_object_id_convert
			[connector_type];
	} else if (((connector_type == DRM_MODE_CONNECTOR_DVII) ||
		    (connector_type == DRM_MODE_CONNECTOR_DVID)) &&
		   (devices & ATOM_DEVICE_DFP2_SUPPORT))  {
		struct radeon_mode_info *mode_info = &rdev->mode_info;
		struct atom_context *ctx = mode_info->atom_context;
		int index = GetIndexIntoMasterTable(DATA, XTMDS_Info);
		uint16_t size, data_offset;
		uint8_t frev, crev;
		ATOM_XTMDS_INFO *xtmds;

		if (atom_parse_data_header(ctx, index, &size, &frev, &crev, &data_offset)) {
			xtmds = (ATOM_XTMDS_INFO *)(ctx->bios + data_offset);

			if (xtmds->ucSupportedLink & ATOM_XTMDS_SUPPORTED_DUALLINK) {
				if (connector_type == DRM_MODE_CONNECTOR_DVII)
					return CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I;
				else
					return CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D;
			} else {
				if (connector_type == DRM_MODE_CONNECTOR_DVII)
					return CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I;
				else
					return CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D;
			}
		} else
			return supported_devices_connector_object_id_convert
				[connector_type];
	} else {
		return supported_devices_connector_object_id_convert
			[connector_type];
	}
}