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
typedef  int u32 ;
struct drm_display_mode {int crtc_hdisplay; } ;
struct amdgpu_device {int flags; int usec_timeout; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct amdgpu_crtc {int crtc_id; int crtc_offset; TYPE_1__ base; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int LB_MEMORY_CTRL__LB_MEMORY_CONFIG__SHIFT ; 
 int LB_MEMORY_CTRL__LB_MEMORY_SIZE__SHIFT ; 
 int PIPE0_DMIF_BUFFER_CONTROL__DMIF_BUFFERS_ALLOCATED__SHIFT ; 
 int PIPE0_DMIF_BUFFER_CONTROL__DMIF_BUFFERS_ALLOCATION_COMPLETED_MASK ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int mmLB_MEMORY_CTRL ; 
 int mmPIPE0_DMIF_BUFFER_CONTROL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u32 dce_v8_0_line_buffer_adjust(struct amdgpu_device *adev,
				       struct amdgpu_crtc *amdgpu_crtc,
				       struct drm_display_mode *mode)
{
	u32 tmp, buffer_alloc, i;
	u32 pipe_offset = amdgpu_crtc->crtc_id * 0x8;
	/*
	 * Line Buffer Setup
	 * There are 6 line buffers, one for each display controllers.
	 * There are 3 partitions per LB. Select the number of partitions
	 * to enable based on the display width.  For display widths larger
	 * than 4096, you need use to use 2 display controllers and combine
	 * them using the stereo blender.
	 */
	if (amdgpu_crtc->base.enabled && mode) {
		if (mode->crtc_hdisplay < 1920) {
			tmp = 1;
			buffer_alloc = 2;
		} else if (mode->crtc_hdisplay < 2560) {
			tmp = 2;
			buffer_alloc = 2;
		} else if (mode->crtc_hdisplay < 4096) {
			tmp = 0;
			buffer_alloc = (adev->flags & AMD_IS_APU) ? 2 : 4;
		} else {
			DRM_DEBUG_KMS("Mode too big for LB!\n");
			tmp = 0;
			buffer_alloc = (adev->flags & AMD_IS_APU) ? 2 : 4;
		}
	} else {
		tmp = 1;
		buffer_alloc = 0;
	}

	WREG32(mmLB_MEMORY_CTRL + amdgpu_crtc->crtc_offset,
	      (tmp << LB_MEMORY_CTRL__LB_MEMORY_CONFIG__SHIFT) |
	      (0x6B0 << LB_MEMORY_CTRL__LB_MEMORY_SIZE__SHIFT));

	WREG32(mmPIPE0_DMIF_BUFFER_CONTROL + pipe_offset,
	       (buffer_alloc << PIPE0_DMIF_BUFFER_CONTROL__DMIF_BUFFERS_ALLOCATED__SHIFT));
	for (i = 0; i < adev->usec_timeout; i++) {
		if (RREG32(mmPIPE0_DMIF_BUFFER_CONTROL + pipe_offset) &
		    PIPE0_DMIF_BUFFER_CONTROL__DMIF_BUFFERS_ALLOCATION_COMPLETED_MASK)
			break;
		udelay(1);
	}

	if (amdgpu_crtc->base.enabled && mode) {
		switch (tmp) {
		case 0:
		default:
			return 4096 * 2;
		case 1:
			return 1920 * 2;
		case 2:
			return 2560 * 2;
		}
	}

	/* controller not enabled, so no lb used */
	return 0;
}