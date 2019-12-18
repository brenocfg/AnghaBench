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
 int /*<<< orphan*/  PIPECONF (int /*<<< orphan*/ ) ; 
 int PIPECONF_ENABLE ; 
 int TRANS_DDI_FUNC_ENABLE ; 
 int /*<<< orphan*/  _PIPE_EDP ; 
 int /*<<< orphan*/  _TRANS_DDI_FUNC_CTL_EDP ; 
 int vgpu_vreg (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int vgpu_vreg_t (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edp_pipe_is_enabled(struct intel_vgpu *vgpu)
{
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;

	if (!(vgpu_vreg_t(vgpu, PIPECONF(_PIPE_EDP)) & PIPECONF_ENABLE))
		return 0;

	if (!(vgpu_vreg(vgpu, _TRANS_DDI_FUNC_CTL_EDP) & TRANS_DDI_FUNC_ENABLE))
		return 0;
	return 1;
}