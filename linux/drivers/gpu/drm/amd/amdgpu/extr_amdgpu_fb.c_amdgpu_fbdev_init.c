#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_fbdev {int /*<<< orphan*/  helper; struct amdgpu_device* adev; } ;
struct TYPE_9__ {struct amdgpu_fbdev* rfbdev; int /*<<< orphan*/  mode_config_initialized; } ;
struct TYPE_8__ {int real_vram_size; } ;
struct amdgpu_device {TYPE_4__* ddev; TYPE_3__ mode_info; TYPE_2__ gmc; } ;
struct TYPE_7__ {int /*<<< orphan*/  connector_list; } ;
struct TYPE_10__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPUFB_CONN_LIMIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_fb_helper_funcs ; 
 int drm_fb_helper_init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_fbdev*) ; 
 struct amdgpu_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int amdgpu_fbdev_init(struct amdgpu_device *adev)
{
	struct amdgpu_fbdev *rfbdev;
	int bpp_sel = 32;
	int ret;

	/* don't init fbdev on hw without DCE */
	if (!adev->mode_info.mode_config_initialized)
		return 0;

	/* don't init fbdev if there are no connectors */
	if (list_empty(&adev->ddev->mode_config.connector_list))
		return 0;

	/* select 8 bpp console on low vram cards */
	if (adev->gmc.real_vram_size <= (32*1024*1024))
		bpp_sel = 8;

	rfbdev = kzalloc(sizeof(struct amdgpu_fbdev), GFP_KERNEL);
	if (!rfbdev)
		return -ENOMEM;

	rfbdev->adev = adev;
	adev->mode_info.rfbdev = rfbdev;

	drm_fb_helper_prepare(adev->ddev, &rfbdev->helper,
			&amdgpu_fb_helper_funcs);

	ret = drm_fb_helper_init(adev->ddev, &rfbdev->helper,
				 AMDGPUFB_CONN_LIMIT);
	if (ret) {
		kfree(rfbdev);
		return ret;
	}

	drm_fb_helper_single_add_all_connectors(&rfbdev->helper);

	/* disable all the possible outputs/crtcs before entering KMS mode */
	if (!amdgpu_device_has_dc_support(adev))
		drm_helper_disable_unused_functions(adev->ddev);

	drm_fb_helper_initial_config(&rfbdev->helper, bpp_sel);
	return 0;
}