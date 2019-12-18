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
struct komeda_kms_dev {int /*<<< orphan*/  base; } ;
struct drm_crtc {int /*<<< orphan*/  port; } ;
struct komeda_crtc {TYPE_1__* master; struct drm_crtc base; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_output_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (int /*<<< orphan*/ *,struct drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_reset (struct drm_crtc*) ; 
 int /*<<< orphan*/  get_crtc_primary (struct komeda_kms_dev*,struct komeda_crtc*) ; 
 int /*<<< orphan*/  komeda_crtc_funcs ; 
 int /*<<< orphan*/  komeda_crtc_helper_funcs ; 

__attribute__((used)) static int komeda_crtc_add(struct komeda_kms_dev *kms,
			   struct komeda_crtc *kcrtc)
{
	struct drm_crtc *crtc = &kcrtc->base;
	int err;

	err = drm_crtc_init_with_planes(&kms->base, crtc,
					get_crtc_primary(kms, kcrtc), NULL,
					&komeda_crtc_funcs, NULL);
	if (err)
		return err;

	drm_crtc_helper_add(crtc, &komeda_crtc_helper_funcs);
	drm_crtc_vblank_reset(crtc);

	crtc->port = kcrtc->master->of_output_port;

	return err;
}