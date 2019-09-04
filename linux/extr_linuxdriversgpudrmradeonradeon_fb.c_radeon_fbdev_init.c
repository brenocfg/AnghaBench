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
struct radeon_fbdev {int /*<<< orphan*/  helper; struct radeon_device* rdev; } ;
struct TYPE_9__ {struct radeon_fbdev* rfbdev; } ;
struct TYPE_8__ {int real_vram_size; } ;
struct radeon_device {TYPE_4__* ddev; TYPE_3__ mode_info; TYPE_2__ mc; } ;
struct TYPE_7__ {int /*<<< orphan*/  connector_list; } ;
struct TYPE_10__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_RN50 (struct radeon_device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADEONFB_CONN_LIMIT ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct radeon_fbdev*) ; 
 struct radeon_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fb_helper_funcs ; 

int radeon_fbdev_init(struct radeon_device *rdev)
{
	struct radeon_fbdev *rfbdev;
	int bpp_sel = 32;
	int ret;

	/* don't enable fbdev if no connectors */
	if (list_empty(&rdev->ddev->mode_config.connector_list))
		return 0;

	/* select 8 bpp console on 8MB cards, or 16 bpp on RN50 or 32MB */
	if (rdev->mc.real_vram_size <= (8*1024*1024))
		bpp_sel = 8;
	else if (ASIC_IS_RN50(rdev) ||
		 rdev->mc.real_vram_size <= (32*1024*1024))
		bpp_sel = 16;

	rfbdev = kzalloc(sizeof(struct radeon_fbdev), GFP_KERNEL);
	if (!rfbdev)
		return -ENOMEM;

	rfbdev->rdev = rdev;
	rdev->mode_info.rfbdev = rfbdev;

	drm_fb_helper_prepare(rdev->ddev, &rfbdev->helper,
			      &radeon_fb_helper_funcs);

	ret = drm_fb_helper_init(rdev->ddev, &rfbdev->helper,
				 RADEONFB_CONN_LIMIT);
	if (ret)
		goto free;

	ret = drm_fb_helper_single_add_all_connectors(&rfbdev->helper);
	if (ret)
		goto fini;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(rdev->ddev);

	ret = drm_fb_helper_initial_config(&rfbdev->helper, bpp_sel);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&rfbdev->helper);
free:
	kfree(rfbdev);
	return ret;
}