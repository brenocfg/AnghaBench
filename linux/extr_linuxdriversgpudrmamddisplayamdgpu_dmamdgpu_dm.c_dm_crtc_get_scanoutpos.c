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
typedef  int uint32_t ;
typedef  int u32 ;
struct dm_crtc_state {int /*<<< orphan*/ * stream; } ;
struct TYPE_3__ {int num_crtc; struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct amdgpu_crtc {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dc_stream_get_scanoutpos (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 struct dm_crtc_state* to_dm_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_crtc_get_scanoutpos(struct amdgpu_device *adev, int crtc,
				  u32 *vbl, u32 *position)
{
	uint32_t v_blank_start, v_blank_end, h_position, v_position;

	if ((crtc < 0) || (crtc >= adev->mode_info.num_crtc))
		return -EINVAL;
	else {
		struct amdgpu_crtc *acrtc = adev->mode_info.crtcs[crtc];
		struct dm_crtc_state *acrtc_state = to_dm_crtc_state(
						acrtc->base.state);

		if (acrtc_state->stream ==  NULL) {
			DRM_ERROR("dc_stream_state is NULL for crtc '%d'!\n",
				  crtc);
			return 0;
		}

		/*
		 * TODO rework base driver to use values directly.
		 * for now parse it back into reg-format
		 */
		dc_stream_get_scanoutpos(acrtc_state->stream,
					 &v_blank_start,
					 &v_blank_end,
					 &h_position,
					 &v_position);

		*position = v_position | (h_position << 16);
		*vbl = v_blank_start | (v_blank_end << 16);
	}

	return 0;
}