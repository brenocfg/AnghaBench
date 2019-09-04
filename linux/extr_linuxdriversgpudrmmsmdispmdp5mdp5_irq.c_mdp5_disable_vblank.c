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
struct msm_kms {int dummy; } ;
struct mdp5_kms {TYPE_1__* pdev; } ;
struct drm_crtc {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdp5_crtc_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp_update_vblank_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 struct mdp5_kms* to_mdp5_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

void mdp5_disable_vblank(struct msm_kms *kms, struct drm_crtc *crtc)
{
	struct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	struct device *dev = &mdp5_kms->pdev->dev;

	pm_runtime_get_sync(dev);
	mdp_update_vblank_mask(to_mdp_kms(kms),
			mdp5_crtc_vblank(crtc), false);
	pm_runtime_put_sync(dev);
}