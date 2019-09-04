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
struct drm_crtc {scalar_t__ y; scalar_t__ x; TYPE_1__* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {int cursor_width; int cursor_x; int cursor_y; int cursor_height; scalar_t__ crtc_offset; scalar_t__ max_cursor_height; scalar_t__ max_cursor_width; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ mmCUR_HOT_SPOT ; 
 scalar_t__ mmCUR_POSITION ; 
 scalar_t__ mmCUR_SIZE ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int dce_v6_0_cursor_move_locked(struct drm_crtc *crtc,
				       int x, int y)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct amdgpu_device *adev = crtc->dev->dev_private;
	int xorigin = 0, yorigin = 0;

	int w = amdgpu_crtc->cursor_width;

	amdgpu_crtc->cursor_x = x;
	amdgpu_crtc->cursor_y = y;

	/* avivo cursor are offset into the total surface */
	x += crtc->x;
	y += crtc->y;
	DRM_DEBUG("x %d y %d c->x %d c->y %d\n", x, y, crtc->x, crtc->y);

	if (x < 0) {
		xorigin = min(-x, amdgpu_crtc->max_cursor_width - 1);
		x = 0;
	}
	if (y < 0) {
		yorigin = min(-y, amdgpu_crtc->max_cursor_height - 1);
		y = 0;
	}

	WREG32(mmCUR_POSITION + amdgpu_crtc->crtc_offset, (x << 16) | y);
	WREG32(mmCUR_HOT_SPOT + amdgpu_crtc->crtc_offset, (xorigin << 16) | yorigin);
	WREG32(mmCUR_SIZE + amdgpu_crtc->crtc_offset,
	       ((w - 1) << 16) | (amdgpu_crtc->cursor_height - 1));

	return 0;
}