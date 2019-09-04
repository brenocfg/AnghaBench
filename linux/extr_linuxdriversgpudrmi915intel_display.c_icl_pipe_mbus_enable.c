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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_4__ {int num_pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 int MBUS_DBOX_A_CREDIT (int) ; 
 int MBUS_DBOX_BW_CREDIT (int) ; 
 int MBUS_DBOX_B_CREDIT (int) ; 
 int /*<<< orphan*/  PIPE_MBUS_DBOX_CTL (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_pipe_mbus_enable(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum pipe pipe = crtc->pipe;
	uint32_t val;

	val = MBUS_DBOX_BW_CREDIT(1) | MBUS_DBOX_A_CREDIT(2);

	/* Program B credit equally to all pipes */
	val |= MBUS_DBOX_B_CREDIT(24 / INTEL_INFO(dev_priv)->num_pipes);

	I915_WRITE(PIPE_MBUS_DBOX_CTL(pipe), val);
}