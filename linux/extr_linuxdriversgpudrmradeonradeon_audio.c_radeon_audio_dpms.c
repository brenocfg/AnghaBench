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
struct radeon_encoder {TYPE_1__* audio; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dpms ) (struct drm_encoder*,int) ;} ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void radeon_audio_dpms(struct drm_encoder *encoder, int mode)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	if (radeon_encoder->audio && radeon_encoder->audio->dpms)
		radeon_encoder->audio->dpms(encoder, mode == DRM_MODE_DPMS_ON);
}