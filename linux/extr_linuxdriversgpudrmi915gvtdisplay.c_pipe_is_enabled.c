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
struct intel_vgpu {TYPE_1__* gvt; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int I915_MAX_PIPES ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_ENABLE ; 
 int PIPE_A ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ edp_pipe_is_enabled (struct intel_vgpu*) ; 
 int get_edp_pipe (struct intel_vgpu*) ; 
 int vgpu_vreg_t (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

int pipe_is_enabled(struct intel_vgpu *vgpu, int pipe)
{
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;

	if (WARN_ON(pipe < PIPE_A || pipe >= I915_MAX_PIPES))
		return -EINVAL;

	if (vgpu_vreg_t(vgpu, PIPECONF(pipe)) & PIPECONF_ENABLE)
		return 1;

	if (edp_pipe_is_enabled(vgpu) &&
			get_edp_pipe(vgpu) == pipe)
		return 1;
	return 0;
}