#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dm_crtc_state {int /*<<< orphan*/ * stream; } ;
struct TYPE_3__ {int num_crtc; struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct amdgpu_crtc {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  dc_stream_get_vblank_counter (int /*<<< orphan*/ *) ; 
 struct dm_crtc_state* to_dm_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dm_vblank_get_counter(struct amdgpu_device *adev, int crtc)
{
	if (crtc >= adev->mode_info.num_crtc)
		return 0;
	else {
		struct amdgpu_crtc *acrtc = adev->mode_info.crtcs[crtc];
		struct dm_crtc_state *acrtc_state = to_dm_crtc_state(
				acrtc->base.state);


		if (acrtc_state->stream == NULL) {
			DRM_ERROR("dc_stream_state is NULL for crtc '%d'!\n",
				  crtc);
			return 0;
		}

		return dc_stream_get_vblank_counter(acrtc_state->stream);
	}
}