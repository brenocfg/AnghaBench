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
typedef  scalar_t__ u32 ;
struct radeon_device {scalar_t__ usec_timeout; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct radeon_crtc {int crtc_id; scalar_t__ crtc_offset; TYPE_1__ base; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LB_MEMORY_CONFIG (scalar_t__) ; 
 scalar_t__ DC_LB_MEMORY_SPLIT ; 
 int /*<<< orphan*/  DMIF_BUFFERS_ALLOCATED (scalar_t__) ; 
 int DMIF_BUFFERS_ALLOCATED_COMPLETED ; 
 scalar_t__ PIPE0_DMIF_BUFFER_CONTROL ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u32 dce6_line_buffer_adjust(struct radeon_device *rdev,
				   struct radeon_crtc *radeon_crtc,
				   struct drm_display_mode *mode,
				   struct drm_display_mode *other_mode)
{
	u32 tmp, buffer_alloc, i;
	u32 pipe_offset = radeon_crtc->crtc_id * 0x20;
	/*
	 * Line Buffer Setup
	 * There are 3 line buffers, each one shared by 2 display controllers.
	 * DC_LB_MEMORY_SPLIT controls how that line buffer is shared between
	 * the display controllers.  The paritioning is done via one of four
	 * preset allocations specified in bits 21:20:
	 *  0 - half lb
	 *  2 - whole lb, other crtc must be disabled
	 */
	/* this can get tricky if we have two large displays on a paired group
	 * of crtcs.  Ideally for multiple large displays we'd assign them to
	 * non-linked crtcs for maximum line buffer allocation.
	 */
	if (radeon_crtc->base.enabled && mode) {
		if (other_mode) {
			tmp = 0; /* 1/2 */
			buffer_alloc = 1;
		} else {
			tmp = 2; /* whole */
			buffer_alloc = 2;
		}
	} else {
		tmp = 0;
		buffer_alloc = 0;
	}

	WREG32(DC_LB_MEMORY_SPLIT + radeon_crtc->crtc_offset,
	       DC_LB_MEMORY_CONFIG(tmp));

	WREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset,
	       DMIF_BUFFERS_ALLOCATED(buffer_alloc));
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(PIPE0_DMIF_BUFFER_CONTROL + pipe_offset) &
		    DMIF_BUFFERS_ALLOCATED_COMPLETED)
			break;
		udelay(1);
	}

	if (radeon_crtc->base.enabled && mode) {
		switch (tmp) {
		case 0:
		default:
			return 4096 * 2;
		case 2:
			return 8192 * 2;
		}
	}

	/* controller not enabled, so no lb used */
	return 0;
}