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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int dpu_crtc_vblank (struct drm_crtc*,int) ; 

__attribute__((used)) static int dpu_kms_enable_vblank(struct msm_kms *kms, struct drm_crtc *crtc)
{
	return dpu_crtc_vblank(crtc, true);
}