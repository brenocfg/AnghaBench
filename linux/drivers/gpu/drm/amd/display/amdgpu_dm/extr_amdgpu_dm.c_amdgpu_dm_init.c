#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int gpu_vm_support; int fbc_support; int multi_mon_pp_mclk_switch; int power_down_display_on_boot; } ;
struct TYPE_14__ {int /*<<< orphan*/  atombios_base_address; int /*<<< orphan*/  vram_width; int /*<<< orphan*/  hw_internal_rev; int /*<<< orphan*/  pci_revision_id; int /*<<< orphan*/  chip_family; } ;
struct dc_init_data {int /*<<< orphan*/  soc_bounding_box; TYPE_4__ flags; int /*<<< orphan*/  dce_environment; scalar_t__ cgs_device; struct amdgpu_device* driver; TYPE_2__ asic_id; } ;
struct TYPE_20__ {int /*<<< orphan*/  display_indexes_num; TYPE_9__* dc; int /*<<< orphan*/  freesync_module; int /*<<< orphan*/  soc_bounding_box; scalar_t__ cgs_device; int /*<<< orphan*/  audio_lock; int /*<<< orphan*/  dc_lock; struct amdgpu_device* adev; TYPE_10__* ddev; } ;
struct TYPE_17__ {int /*<<< orphan*/  num_crtc; TYPE_3__* atom_context; } ;
struct TYPE_13__ {int /*<<< orphan*/  vram_width; } ;
struct amdgpu_device {int flags; scalar_t__ asic_type; TYPE_8__ dm; TYPE_10__* ddev; TYPE_5__ mode_info; TYPE_1__ gmc; int /*<<< orphan*/  external_rev_id; int /*<<< orphan*/  rev_id; int /*<<< orphan*/  family; } ;
typedef  int /*<<< orphan*/  init_data ;
struct TYPE_19__ {int /*<<< orphan*/  max_cursor_size; } ;
struct TYPE_21__ {TYPE_7__ caps; } ;
struct TYPE_18__ {int /*<<< orphan*/  cursor_height; int /*<<< orphan*/  cursor_width; } ;
struct TYPE_15__ {int /*<<< orphan*/  bios; } ;
struct TYPE_12__ {TYPE_6__ mode_config; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 scalar_t__ CHIP_CARRIZO ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  DCE_ENV_PRODUCTION_DRV ; 
 int DC_FBC_MASK ; 
 int DC_MULTI_MON_PP_MCLK_SWITCH_MASK ; 
 int /*<<< orphan*/  DC_VER ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ amdgpu_cgs_create_device (struct amdgpu_device*) ; 
 int amdgpu_dc_feature_mask ; 
 int /*<<< orphan*/  amdgpu_dm_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dm_init_color_mod () ; 
 scalar_t__ amdgpu_dm_initialize_drm_device (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_dm_irq_init (struct amdgpu_device*) ; 
 TYPE_9__* dc_create (struct dc_init_data*) ; 
 scalar_t__ drm_vblank_init (TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dtn_debugfs_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  memset (struct dc_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_freesync_create (TYPE_9__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_dm_init(struct amdgpu_device *adev)
{
	struct dc_init_data init_data;
	adev->dm.ddev = adev->ddev;
	adev->dm.adev = adev;

	/* Zero all the fields */
	memset(&init_data, 0, sizeof(init_data));

	mutex_init(&adev->dm.dc_lock);
	mutex_init(&adev->dm.audio_lock);

	if(amdgpu_dm_irq_init(adev)) {
		DRM_ERROR("amdgpu: failed to initialize DM IRQ support.\n");
		goto error;
	}

	init_data.asic_id.chip_family = adev->family;

	init_data.asic_id.pci_revision_id = adev->rev_id;
	init_data.asic_id.hw_internal_rev = adev->external_rev_id;

	init_data.asic_id.vram_width = adev->gmc.vram_width;
	/* TODO: initialize init_data.asic_id.vram_type here!!!! */
	init_data.asic_id.atombios_base_address =
		adev->mode_info.atom_context->bios;

	init_data.driver = adev;

	adev->dm.cgs_device = amdgpu_cgs_create_device(adev);

	if (!adev->dm.cgs_device) {
		DRM_ERROR("amdgpu: failed to create cgs device.\n");
		goto error;
	}

	init_data.cgs_device = adev->dm.cgs_device;

	init_data.dce_environment = DCE_ENV_PRODUCTION_DRV;

	/*
	 * TODO debug why this doesn't work on Raven
	 */
	if (adev->flags & AMD_IS_APU &&
	    adev->asic_type >= CHIP_CARRIZO &&
	    adev->asic_type <= CHIP_RAVEN)
		init_data.flags.gpu_vm_support = true;

	if (amdgpu_dc_feature_mask & DC_FBC_MASK)
		init_data.flags.fbc_support = true;

	if (amdgpu_dc_feature_mask & DC_MULTI_MON_PP_MCLK_SWITCH_MASK)
		init_data.flags.multi_mon_pp_mclk_switch = true;

	init_data.flags.power_down_display_on_boot = true;

#ifdef CONFIG_DRM_AMD_DC_DCN2_0
	init_data.soc_bounding_box = adev->dm.soc_bounding_box;
#endif

	/* Display Core create. */
	adev->dm.dc = dc_create(&init_data);

	if (adev->dm.dc) {
		DRM_INFO("Display Core initialized with v%s!\n", DC_VER);
	} else {
		DRM_INFO("Display Core failed to initialize with v%s!\n", DC_VER);
		goto error;
	}

	adev->dm.freesync_module = mod_freesync_create(adev->dm.dc);
	if (!adev->dm.freesync_module) {
		DRM_ERROR(
		"amdgpu: failed to initialize freesync_module.\n");
	} else
		DRM_DEBUG_DRIVER("amdgpu: freesync_module init done %p.\n",
				adev->dm.freesync_module);

	amdgpu_dm_init_color_mod();

	if (amdgpu_dm_initialize_drm_device(adev)) {
		DRM_ERROR(
		"amdgpu: failed to initialize sw for display support.\n");
		goto error;
	}

	/* Update the actual used number of crtc */
	adev->mode_info.num_crtc = adev->dm.display_indexes_num;

	/* TODO: Add_display_info? */

	/* TODO use dynamic cursor width */
	adev->ddev->mode_config.cursor_width = adev->dm.dc->caps.max_cursor_size;
	adev->ddev->mode_config.cursor_height = adev->dm.dc->caps.max_cursor_size;

	if (drm_vblank_init(adev->ddev, adev->dm.display_indexes_num)) {
		DRM_ERROR(
		"amdgpu: failed to initialize sw for display support.\n");
		goto error;
	}

#if defined(CONFIG_DEBUG_FS)
	if (dtn_debugfs_init(adev))
		DRM_ERROR("amdgpu: failed initialize dtn debugfs support.\n");
#endif

	DRM_DEBUG_DRIVER("KMS initialized.\n");

	return 0;
error:
	amdgpu_dm_fini(adev);

	return -EINVAL;
}