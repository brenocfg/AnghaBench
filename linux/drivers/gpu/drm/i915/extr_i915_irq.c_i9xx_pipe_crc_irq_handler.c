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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_CRC_RES_BLUE (int) ; 
 int /*<<< orphan*/  PIPE_CRC_RES_GREEN (int) ; 
 int /*<<< orphan*/  PIPE_CRC_RES_RED (int) ; 
 int /*<<< orphan*/  PIPE_CRC_RES_RES1_I915 (int) ; 
 int /*<<< orphan*/  PIPE_CRC_RES_RES2_G4X (int) ; 
 int /*<<< orphan*/  display_pipe_crc_irq_handler (struct drm_i915_private*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void i9xx_pipe_crc_irq_handler(struct drm_i915_private *dev_priv,
				      enum pipe pipe)
{
	u32 res1, res2;

	if (INTEL_GEN(dev_priv) >= 3)
		res1 = I915_READ(PIPE_CRC_RES_RES1_I915(pipe));
	else
		res1 = 0;

	if (INTEL_GEN(dev_priv) >= 5 || IS_G4X(dev_priv))
		res2 = I915_READ(PIPE_CRC_RES_RES2_G4X(pipe));
	else
		res2 = 0;

	display_pipe_crc_irq_handler(dev_priv, pipe,
				     I915_READ(PIPE_CRC_RES_RED(pipe)),
				     I915_READ(PIPE_CRC_RES_GREEN(pipe)),
				     I915_READ(PIPE_CRC_RES_BLUE(pipe)),
				     res1, res2);
}