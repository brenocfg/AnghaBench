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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  argb8888; } ;
typedef  struct dc_plane_cap {scalar_t__ type; TYPE_1__ pixel_format_support; int /*<<< orphan*/  blends_with_below; int /*<<< orphan*/  blends_with_above; } const dc_plane_cap ;
struct dc_link {int dummy; } ;
struct amdgpu_mode_info {int /*<<< orphan*/ * planes; } ;
struct TYPE_8__ {scalar_t__ force; } ;
struct amdgpu_encoder {TYPE_3__ base; } ;
struct amdgpu_dm_connector {TYPE_3__ base; } ;
struct amdgpu_display_manager {int display_indexes_num; TYPE_5__* dc; int /*<<< orphan*/  adev; int /*<<< orphan*/  ddev; } ;
struct amdgpu_device {int asic_type; struct amdgpu_mode_info mode_info; struct amdgpu_display_manager dm; } ;
typedef  int int32_t ;
typedef  enum dc_connection_type { ____Placeholder_dc_connection_type } dc_connection_type ;
struct TYPE_9__ {int disable_stutter; } ;
struct TYPE_7__ {int max_links; int max_streams; int max_planes; struct dc_plane_cap const* planes; } ;
struct TYPE_10__ {TYPE_4__ debug; TYPE_2__ caps; } ;

/* Variables and functions */
 int AMDGPU_DM_MAX_DISPLAY_INDEX ; 
 int AMDGPU_MAX_PLANES ; 
 int /*<<< orphan*/  ASSERT (int) ; 
#define  CHIP_BONAIRE 148 
#define  CHIP_CARRIZO 147 
#define  CHIP_FIJI 146 
#define  CHIP_HAWAII 145 
#define  CHIP_KABINI 144 
#define  CHIP_KAVERI 143 
#define  CHIP_MULLINS 142 
#define  CHIP_NAVI10 141 
#define  CHIP_NAVI12 140 
#define  CHIP_NAVI14 139 
#define  CHIP_POLARIS10 138 
#define  CHIP_POLARIS11 137 
#define  CHIP_POLARIS12 136 
#define  CHIP_RAVEN 135 
#define  CHIP_RENOIR 134 
#define  CHIP_STONEY 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 scalar_t__ DC_PLANE_TYPE_DCN_UNIVERSAL ; 
 int /*<<< orphan*/  DETECT_REASON_BOOT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PP_STUTTER_MODE ; 
 scalar_t__ amdgpu_dm_connector_init (struct amdgpu_display_manager*,struct amdgpu_encoder*,int,struct amdgpu_encoder*) ; 
 scalar_t__ amdgpu_dm_crtc_init (struct amdgpu_display_manager*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_dm_encoder_init (int /*<<< orphan*/ ,struct amdgpu_encoder*,int) ; 
 scalar_t__ amdgpu_dm_mode_config_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dm_update_connector_after_detect (struct amdgpu_encoder*) ; 
 int amdgpu_pp_feature_mask ; 
 int dc_connection_none ; 
 struct dc_link* dc_get_link_at_index (TYPE_5__*,int) ; 
 scalar_t__ dc_link_detect (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_link_detect_sink (struct dc_link*,int*) ; 
 int /*<<< orphan*/  dce110_register_irq_handlers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcn10_register_irq_handlers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emulated_link_detect (struct dc_link*) ; 
 scalar_t__ initialize_plane (struct amdgpu_display_manager*,struct amdgpu_mode_info*,int,int /*<<< orphan*/ ,struct dc_plane_cap const*) ; 
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
	int32_t primary_planes;
	enum dc_connection_type new_connection_type = dc_connection_none;
	const struct dc_plane_cap *plane;

	link_cnt = dm->dc->caps.max_links;
	if (amdgpu_dm_mode_config_init(dm->adev)) {
		DRM_ERROR("DM: Failed to initialize mode config\n");
		return -EINVAL;
	}

	/* There is one primary plane per CRTC */
	primary_planes = dm->dc->caps.max_streams;
	ASSERT(primary_planes <= AMDGPU_MAX_PLANES);

	/*
	 * Initialize primary planes, implicit planes for legacy IOCTLS.
	 * Order is reversed to match iteration order in atomic check.
	 */
	for (i = (primary_planes - 1); i >= 0; i--) {
		plane = &dm->dc->caps.planes[i];

		if (initialize_plane(dm, mode_info, i,
				     DRM_PLANE_TYPE_PRIMARY, plane)) {
			DRM_ERROR("KMS: Failed to initialize primary plane\n");
			goto fail;
		}
	}

	/*
	 * Initialize overlay planes, index starting after primary planes.
	 * These planes have a higher DRM index than the primary planes since
	 * they should be considered as having a higher z-order.
	 * Order is reversed to match iteration order in atomic check.
	 *
	 * Only support DCN for now, and only expose one so we don't encourage
	 * userspace to use up all the pipes.
	 */
	for (i = 0; i < dm->dc->caps.max_planes; ++i) {
		struct dc_plane_cap *plane = &dm->dc->caps.planes[i];

		if (plane->type != DC_PLANE_TYPE_DCN_UNIVERSAL)
			continue;

		if (!plane->blends_with_above || !plane->blends_with_below)
			continue;

		if (!plane->pixel_format_support.argb8888)
			continue;

		if (initialize_plane(dm, NULL, primary_planes + i,
				     DRM_PLANE_TYPE_OVERLAY, plane)) {
			DRM_ERROR("KMS: Failed to initialize overlay plane\n");
			goto fail;
		}

		/* Only create one overlay plane. */
		break;
	}

	for (i = 0; i < dm->dc->caps.max_streams; i++)
		if (amdgpu_dm_crtc_init(dm, mode_info->planes[i], i)) {
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
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	case CHIP_NAVI12:
	case CHIP_NAVI10:
	case CHIP_NAVI14:
#endif
#if defined(CONFIG_DRM_AMD_DC_DCN2_1)
	case CHIP_RENOIR:
#endif
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

	return -EINVAL;
}