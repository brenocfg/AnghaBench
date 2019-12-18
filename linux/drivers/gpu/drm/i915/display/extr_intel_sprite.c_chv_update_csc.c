#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t color_encoding; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int id; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
struct TYPE_6__ {int /*<<< orphan*/  is_yuv; } ;

/* Variables and functions */
#define  DRM_COLOR_YCBCR_BT601 129 
#define  DRM_COLOR_YCBCR_BT709 128 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPCSCC01 (int) ; 
 int /*<<< orphan*/  SPCSCC23 (int) ; 
 int /*<<< orphan*/  SPCSCC45 (int) ; 
 int /*<<< orphan*/  SPCSCC67 (int) ; 
 int /*<<< orphan*/  SPCSCC8 (int) ; 
 int /*<<< orphan*/  SPCSCCBICLAMP (int) ; 
 int /*<<< orphan*/  SPCSCCBOCLAMP (int) ; 
 int /*<<< orphan*/  SPCSCCBOFF (int) ; 
 int /*<<< orphan*/  SPCSCCRICLAMP (int) ; 
 int /*<<< orphan*/  SPCSCCROCLAMP (int) ; 
 int /*<<< orphan*/  SPCSCCROFF (int) ; 
 int /*<<< orphan*/  SPCSCYGICLAMP (int) ; 
 int /*<<< orphan*/  SPCSCYGOCLAMP (int) ; 
 int /*<<< orphan*/  SPCSCYGOFF (int) ; 
 int SPCSC_C0 (int /*<<< orphan*/  const) ; 
 int SPCSC_C1 (int /*<<< orphan*/  const) ; 
 int SPCSC_IMAX (int) ; 
 int SPCSC_IMIN (int) ; 
 int SPCSC_IOFF (int /*<<< orphan*/ ) ; 
 int SPCSC_OMAX (int) ; 
 int SPCSC_OMIN (int /*<<< orphan*/ ) ; 
 int SPCSC_OOFF (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chv_update_csc(const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	enum plane_id plane_id = plane->id;
	/*
	 * |r|   | c0 c1 c2 |   |cr|
	 * |g| = | c3 c4 c5 | x |y |
	 * |b|   | c6 c7 c8 |   |cb|
	 *
	 * Coefficients are s3.12.
	 *
	 * Cb and Cr apparently come in as signed already, and
	 * we always get full range data in on account of CLRC0/1.
	 */
	static const s16 csc_matrix[][9] = {
		/* BT.601 full range YCbCr -> full range RGB */
		[DRM_COLOR_YCBCR_BT601] = {
			 5743, 4096,     0,
			-2925, 4096, -1410,
			    0, 4096,  7258,
		},
		/* BT.709 full range YCbCr -> full range RGB */
		[DRM_COLOR_YCBCR_BT709] = {
			 6450, 4096,     0,
			-1917, 4096,  -767,
			    0, 4096,  7601,
		},
	};
	const s16 *csc = csc_matrix[plane_state->base.color_encoding];

	/* Seems RGB data bypasses the CSC always */
	if (!fb->format->is_yuv)
		return;

	I915_WRITE_FW(SPCSCYGOFF(plane_id), SPCSC_OOFF(0) | SPCSC_IOFF(0));
	I915_WRITE_FW(SPCSCCBOFF(plane_id), SPCSC_OOFF(0) | SPCSC_IOFF(0));
	I915_WRITE_FW(SPCSCCROFF(plane_id), SPCSC_OOFF(0) | SPCSC_IOFF(0));

	I915_WRITE_FW(SPCSCC01(plane_id), SPCSC_C1(csc[1]) | SPCSC_C0(csc[0]));
	I915_WRITE_FW(SPCSCC23(plane_id), SPCSC_C1(csc[3]) | SPCSC_C0(csc[2]));
	I915_WRITE_FW(SPCSCC45(plane_id), SPCSC_C1(csc[5]) | SPCSC_C0(csc[4]));
	I915_WRITE_FW(SPCSCC67(plane_id), SPCSC_C1(csc[7]) | SPCSC_C0(csc[6]));
	I915_WRITE_FW(SPCSCC8(plane_id), SPCSC_C0(csc[8]));

	I915_WRITE_FW(SPCSCYGICLAMP(plane_id), SPCSC_IMAX(1023) | SPCSC_IMIN(0));
	I915_WRITE_FW(SPCSCCBICLAMP(plane_id), SPCSC_IMAX(512) | SPCSC_IMIN(-512));
	I915_WRITE_FW(SPCSCCRICLAMP(plane_id), SPCSC_IMAX(512) | SPCSC_IMIN(-512));

	I915_WRITE_FW(SPCSCYGOCLAMP(plane_id), SPCSC_OMAX(1023) | SPCSC_OMIN(0));
	I915_WRITE_FW(SPCSCCBOCLAMP(plane_id), SPCSC_OMAX(1023) | SPCSC_OMIN(0));
	I915_WRITE_FW(SPCSCCROCLAMP(plane_id), SPCSC_OMAX(1023) | SPCSC_OMIN(0));
}