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
struct TYPE_2__ {struct mga_crtc* crtc; } ;
struct mga_device {TYPE_1__ mode_info; int /*<<< orphan*/  dev; } ;
struct mga_crtc {int /*<<< orphan*/  base; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MGAG200FB_CONN_LIMIT ; 
 int /*<<< orphan*/  MGAG200_LUT_SIZE ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mga_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_crtc_funcs ; 
 int /*<<< orphan*/  mga_helper_funcs ; 

__attribute__((used)) static void mga_crtc_init(struct mga_device *mdev)
{
	struct mga_crtc *mga_crtc;

	mga_crtc = kzalloc(sizeof(struct mga_crtc) +
			      (MGAG200FB_CONN_LIMIT * sizeof(struct drm_connector *)),
			      GFP_KERNEL);

	if (mga_crtc == NULL)
		return;

	drm_crtc_init(mdev->dev, &mga_crtc->base, &mga_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&mga_crtc->base, MGAG200_LUT_SIZE);
	mdev->mode_info.crtc = mga_crtc;

	drm_crtc_helper_add(&mga_crtc->base, &mga_helper_funcs);
}