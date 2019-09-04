#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dc_link {TYPE_3__* link_enc; } ;
struct TYPE_13__ {int interlace_allowed; int doublescan_allowed; int stereo_allowed; int ycbcr_420_allowed; int /*<<< orphan*/  base; void* polled; int /*<<< orphan*/  dpms; } ;
struct TYPE_8__ {int /*<<< orphan*/  hpd; } ;
struct amdgpu_dm_connector {int connector_id; TYPE_6__ base; int /*<<< orphan*/  hpd_lock; TYPE_1__ hpd; struct dc_link* dc_link; } ;
struct amdgpu_display_manager {TYPE_5__* ddev; } ;
struct TYPE_14__ {int /*<<< orphan*/  max_bpc_property; int /*<<< orphan*/  underscan_vborder_property; int /*<<< orphan*/  underscan_hborder_property; int /*<<< orphan*/  underscan_property; } ;
struct amdgpu_device {TYPE_7__ mode_info; } ;
struct TYPE_11__ {int /*<<< orphan*/  scaling_mode_property; } ;
struct TYPE_12__ {TYPE_4__ mode_config; struct amdgpu_device* dev_private; } ;
struct TYPE_9__ {int /*<<< orphan*/  ycbcr420_supported; } ;
struct TYPE_10__ {TYPE_2__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_HPD_NONE ; 
 void* DRM_CONNECTOR_POLL_HPD ; 
#define  DRM_MODE_CONNECTOR_DVID 130 
#define  DRM_MODE_CONNECTOR_DisplayPort 129 
#define  DRM_MODE_CONNECTOR_HDMIA 128 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_NONE ; 
 int /*<<< orphan*/  UNDERSCAN_OFF ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void amdgpu_dm_connector_init_helper(struct amdgpu_display_manager *dm,
				     struct amdgpu_dm_connector *aconnector,
				     int connector_type,
				     struct dc_link *link,
				     int link_index)
{
	struct amdgpu_device *adev = dm->ddev->dev_private;

	aconnector->connector_id = link_index;
	aconnector->dc_link = link;
	aconnector->base.interlace_allowed = false;
	aconnector->base.doublescan_allowed = false;
	aconnector->base.stereo_allowed = false;
	aconnector->base.dpms = DRM_MODE_DPMS_OFF;
	aconnector->hpd.hpd = AMDGPU_HPD_NONE; /* not used */
	mutex_init(&aconnector->hpd_lock);

	/* configure support HPD hot plug connector_>polled default value is 0
	 * which means HPD hot plug not supported
	 */
	switch (connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		aconnector->base.polled = DRM_CONNECTOR_POLL_HPD;
		aconnector->base.ycbcr_420_allowed =
			link->link_enc->features.ycbcr420_supported ? true : false;
		break;
	case DRM_MODE_CONNECTOR_DisplayPort:
		aconnector->base.polled = DRM_CONNECTOR_POLL_HPD;
		aconnector->base.ycbcr_420_allowed =
			link->link_enc->features.ycbcr420_supported ? true : false;
		break;
	case DRM_MODE_CONNECTOR_DVID:
		aconnector->base.polled = DRM_CONNECTOR_POLL_HPD;
		break;
	default:
		break;
	}

	drm_object_attach_property(&aconnector->base.base,
				dm->ddev->mode_config.scaling_mode_property,
				DRM_MODE_SCALE_NONE);

	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.underscan_property,
				UNDERSCAN_OFF);
	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.underscan_hborder_property,
				0);
	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.underscan_vborder_property,
				0);
	drm_object_attach_property(&aconnector->base.base,
				adev->mode_info.max_bpc_property,
				0);

}