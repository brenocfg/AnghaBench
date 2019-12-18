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
struct intel_crtc_state {int dummy; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_check_cpu_fifo_underruns (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_check_pch_fifo_underruns (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void
intel_post_enable_primary(struct drm_crtc *crtc,
			  const struct intel_crtc_state *new_crtc_state)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	int pipe = intel_crtc->pipe;

	/*
	 * Gen2 reports pipe underruns whenever all planes are disabled.
	 * So don't enable underrun reporting before at least some planes
	 * are enabled.
	 * FIXME: Need to fix the logic to work when we turn off all planes
	 * but leave the pipe running.
	 */
	if (IS_GEN(dev_priv, 2))
		intel_set_cpu_fifo_underrun_reporting(dev_priv, pipe, true);

	/* Underruns don't always raise interrupts, so check manually. */
	intel_check_cpu_fifo_underruns(dev_priv);
	intel_check_pch_fifo_underruns(dev_priv);
}