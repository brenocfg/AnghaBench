#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_kms {int dummy; } ;
struct mdp4_kms {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdp4_crtc_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp4_disable (struct mdp4_kms*) ; 
 int /*<<< orphan*/  mdp4_enable (struct mdp4_kms*) ; 
 int /*<<< orphan*/  mdp_update_vblank_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mdp4_kms* to_mdp4_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

int mdp4_enable_vblank(struct msm_kms *kms, struct drm_crtc *crtc)
{
	struct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));

	mdp4_enable(mdp4_kms);
	mdp_update_vblank_mask(to_mdp_kms(kms),
			mdp4_crtc_vblank(crtc), true);
	mdp4_disable(mdp4_kms);

	return 0;
}