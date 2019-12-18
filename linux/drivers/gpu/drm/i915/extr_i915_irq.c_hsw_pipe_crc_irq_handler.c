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
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_CRC_RES_1_IVB (int) ; 
 int /*<<< orphan*/  display_pipe_crc_irq_handler (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_pipe_crc_irq_handler(struct drm_i915_private *dev_priv,
				     enum pipe pipe)
{
	display_pipe_crc_irq_handler(dev_priv, pipe,
				     I915_READ(PIPE_CRC_RES_1_IVB(pipe)),
				     0, 0, 0, 0);
}