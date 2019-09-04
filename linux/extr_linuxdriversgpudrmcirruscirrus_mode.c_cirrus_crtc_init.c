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
struct drm_device {struct cirrus_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {struct cirrus_crtc* crtc; } ;
struct cirrus_device {TYPE_1__ mode_info; } ;
struct cirrus_crtc {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int CIRRUSFB_CONN_LIMIT ; 
 int /*<<< orphan*/  CIRRUS_LUT_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cirrus_crtc_funcs ; 
 int /*<<< orphan*/  cirrus_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cirrus_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cirrus_crtc_init(struct drm_device *dev)
{
	struct cirrus_device *cdev = dev->dev_private;
	struct cirrus_crtc *cirrus_crtc;

	cirrus_crtc = kzalloc(sizeof(struct cirrus_crtc) +
			      (CIRRUSFB_CONN_LIMIT * sizeof(struct drm_connector *)),
			      GFP_KERNEL);

	if (cirrus_crtc == NULL)
		return;

	drm_crtc_init(dev, &cirrus_crtc->base, &cirrus_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&cirrus_crtc->base, CIRRUS_LUT_SIZE);
	cdev->mode_info.crtc = cirrus_crtc;

	drm_crtc_helper_add(&cirrus_crtc->base, &cirrus_helper_funcs);
}