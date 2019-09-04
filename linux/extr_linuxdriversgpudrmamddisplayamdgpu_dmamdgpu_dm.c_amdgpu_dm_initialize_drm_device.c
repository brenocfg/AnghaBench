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
typedef  size_t uint32_t ;
struct dc_link {int dummy; } ;
struct amdgpu_mode_info {struct amdgpu_encoder** planes; } ;
struct TYPE_8__ {scalar_t__ force; } ;
struct amdgpu_encoder {TYPE_4__ base; } ;
struct amdgpu_dm_connector {TYPE_4__ base; } ;
struct amdgpu_display_manager {size_t display_indexes_num; TYPE_3__* dc; int /*<<< orphan*/  adev; int /*<<< orphan*/  ddev; } ;
struct amdgpu_device {int asic_type; struct amdgpu_mode_info mode_info; struct amdgpu_display_manager dm; } ;
typedef  size_t int32_t ;
typedef  enum dc_connection_type { ____Placeholder_dc_connection_type } dc_connection_type ;
struct TYPE_6__ {size_t max_links; size_t max_slave_planes; size_t max_planes; size_t max_streams; } ;
struct TYPE_5__ {int disable_stutter; } ;
struct TYPE_7__ {TYPE_2__ caps; TYPE_1__ debug; } ;

/* Variables and functions */
 size_t AMDGPU_DM_MAX_DISPLAY_INDEX ; 
#define  CHIP_BONAIRE 143 
#define  CHIP_CARRIZO 142 
#define  CHIP_FIJI 141 
#define  CHIP_HAWAII 140 
#define  CHIP_KABINI 139 
#define  CHIP_KAVERI 138 
#define  CHIP_MULLINS 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_POLARIS12 134 
#define  CHIP_STONEY 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DETECT_REASON_BOOT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PP_STUTTER_MODE ; 
 scalar_t__ amdgpu_dm_connector_init (struct amdgpu_display_manager*,struct amdgpu_encoder*,size_t,struct amdgpu_encoder*) ; 
 scalar_t__ amdgpu_dm_crtc_init (struct amdgpu_display_manager*,TYPE_4__*,size_t) ; 
 scalar_t__ amdgpu_dm_encoder_init (int /*<<< orphan*/ ,struct amdgpu_encoder*,size_t) ; 
 scalar_t__ amdgpu_dm_mode_config_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dm_update_connector_after_detect (struct amdgpu_encoder*) ; 
 int amdgpu_pp_feature_mask ; 
 int dc_connection_none ; 
 struct dc_link* dc_get_link_at_index (TYPE_3__*,size_t) ; 
 scalar_t__ dc_link_detect (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_link_detect_sink (struct dc_link*,int*) ; 
 int /*<<< orphan*/  dce110_register_irq_handlers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emulated_link_detect (struct dc_link*) ; 
 scalar_t__ initialize_plane (struct amdgpu_display_manager*,struct amdgpu_mode_info*,size_t) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_encoder*) ; 
 struct amdgpu_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_backlight_device (struct amdgpu_display_manager*,struct dc_link*) ; 

__attribute__((used)) static int amdgpu_dm_initialize_drm_device(struct amdgpu_device *adev)
{
	struct amdgpu_display_manager *dm = &adev->dm;
	int32_t i;
	struct amdgpu_dm_connector *aconnector = NULL;
	struct amdgpu_encoder *aencoder = NULL;
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	uint32_t link_cnt;
	int32_t total_overlay_planes, total_primary_planes;
	enum dc_connection_type new_connection_type = dc_connection_none;

	link_cnt = dm->dc->caps.max_links;
	if (amdgpu_dm_mode_config_init(dm->adev)) {
		DRM_ERROR("DM: Failed to initialize mode config\n");
		return -1;
	}

	/* Identify the number of planes to be initialized */
	total_overlay_planes = dm->dc->caps.max_slave_planes;
	total_primary_planes = dm->dc->caps.max_planes - dm->dc->caps.max_slave_planes;

	/* First initialize overlay planes, index starting after primary planes */
	for (i = (total_overlay_planes - 1); i >= 0; i--) {
		if (initialize_plane(dm, mode_info, (total_primary_planes + i))) {
			DRM_ERROR("KMS: Failed to initialize overlay plane\n");
			goto fail;
		}
	}

	/* Initialize primary planes */
	for (i = (total_primary_planes - 1); i >= 0; i--) {
		if (initialize_plane(dm, mode_info, i)) {
			DRM_ERROR("KMS: Failed to initialize primary plane\n");
			goto fail;
		}
	}

	for (i = 0; i < dm->dc->caps.max_streams; i++)
		if (amdgpu_dm_crtc_init(dm, &mode_info->planes[i]->base, i)) {
			DRM_ERROR("KMS: Failed to initialize crtc\n");
			goto fail;
		}

	dm->display_indexes_num = dm->dc->caps.max_streams;

	/* loops over all connectors on the board */
	for (i = 0; i < link_cnt; i++) {
		struct dc_link *link = NULL;

		if (i > AMDGPU_DM_MAX_DISPLAY_INDEX) {
			DRM_ERROR(
				"KMS: Cannot support more than %d display indexes\n",
					AMDGPU_DM_MAX_DISPLAY_INDEX);
			continue;
		}

		aconnector = kzalloc(sizeof(*aconnector), GFP_KERNEL);
		if (!aconnector)
			goto fail;

		aencoder = kzalloc(sizeof(*aencoder), GFP_KERNEL);
		if (!aencoder)
			goto fail;

		if (amdgpu_dm_encoder_init(dm->ddev, aencoder, i)) {
			DRM_ERROR("KMS: Failed to initialize encoder\n");
			goto fail;
		}

		if (amdgpu_dm_connector_init(dm, aconnector, i, aencoder)) {
			DRM_ERROR("KMS: Failed to initialize connector\n");
			goto fail;
		}

		link = dc_get_link_at_index(dm->dc, i);

		if (!dc_link_detect_sink(link, &new_connection_type))
			DRM_ERROR("KMS: Failed to detect connector\n");

		if (aconnector->base.force && new_connection_type == dc_connection_none) {
			emulated_link_detect(link);
			amdgpu_dm_update_connector_after_detect(aconnector);

		} else if (dc_link_detect(link, DETECT_REASON_BOOT)) {
			amdgpu_dm_update_connector_after_detect(aconnector);
			register_backlight_device(dm, link);
		}


	}

	/* Software is initialized. Now we can register interrupt handlers. */
	switch (adev->asic_type) {
	case CHIP_BONAIRE:
	case CHIP_HAWAII:
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_MULLINS:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_CARRIZO:
	case CHIP_STONEY:
	case CHIP_POLARIS11:
	case CHIP_POLARIS10:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		if (dce110_register_irq_handlers(dm->adev)) {
			DRM_ERROR("DM: Failed to initialize IRQ\n");
			goto fail;
		}
		break;
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case CHIP_RAVEN:
		if (dcn10_register_irq_handlers(dm->adev)) {
			DRM_ERROR("DM: Failed to initialize IRQ\n");
			goto fail;
		}
		break;
#endif
	default:
		DRM_ERROR("Unsupported ASIC type: 0x%X\n", adev->asic_type);
		goto fail;
	}

	if (adev->asic_type != CHIP_CARRIZO && adev->asic_type != CHIP_STONEY)
		dm->dc->debug.disable_stutter = amdgpu_pp_feature_mask & PP_STUTTER_MODE ? false : true;

	return 0;
fail:
	kfree(aencoder);
	kfree(aconnector);
	for (i = 0; i < dm->dc->caps.max_planes; i++)
		kfree(mode_info->planes[i]);
	return -1;
}