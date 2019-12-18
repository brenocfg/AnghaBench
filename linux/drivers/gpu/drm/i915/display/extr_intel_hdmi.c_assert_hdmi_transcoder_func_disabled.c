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
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_FUNC_ENABLE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void
assert_hdmi_transcoder_func_disabled(struct drm_i915_private *dev_priv,
				     enum transcoder cpu_transcoder)
{
	WARN(I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder)) &
	     TRANS_DDI_FUNC_ENABLE,
	     "HDMI transcoder function enabled, expecting disabled\n");
}