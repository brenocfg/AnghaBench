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
typedef  int u16 ;
struct TYPE_5__ {struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_6__ {int /*<<< orphan*/  is_yuv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVSGAMCMAX_ILK (int,int) ; 
 int /*<<< orphan*/  DVSGAMC_ILK (int,int) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ilk_sprite_linear_gamma (int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_update_gamma(const struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	enum pipe pipe = plane->pipe;
	u16 gamma[17];
	int i;

	/* Seems RGB data bypasses the gamma always */
	if (!fb->format->is_yuv)
		return;

	ilk_sprite_linear_gamma(gamma);

	/* FIXME these register are single buffered :( */
	for (i = 0; i < 16; i++)
		I915_WRITE_FW(DVSGAMC_ILK(pipe, i),
			      gamma[i] << 20 |
			      gamma[i] << 10 |
			      gamma[i]);

	I915_WRITE_FW(DVSGAMCMAX_ILK(pipe, 0), gamma[i]);
	I915_WRITE_FW(DVSGAMCMAX_ILK(pipe, 1), gamma[i]);
	I915_WRITE_FW(DVSGAMCMAX_ILK(pipe, 2), gamma[i]);
	i++;
}