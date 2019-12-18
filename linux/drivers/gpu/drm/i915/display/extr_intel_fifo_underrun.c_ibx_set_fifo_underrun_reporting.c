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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int PIPE_A ; 
 int /*<<< orphan*/  SDE_TRANSA_FIFO_UNDER ; 
 int /*<<< orphan*/  SDE_TRANSB_FIFO_UNDER ; 
 int /*<<< orphan*/  ibx_disable_display_interrupt (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_enable_display_interrupt (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void ibx_set_fifo_underrun_reporting(struct drm_device *dev,
					    enum pipe pch_transcoder,
					    bool enable)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 bit = (pch_transcoder == PIPE_A) ?
		SDE_TRANSA_FIFO_UNDER : SDE_TRANSB_FIFO_UNDER;

	if (enable)
		ibx_enable_display_interrupt(dev_priv, bit);
	else
		ibx_disable_display_interrupt(dev_priv, bit);
}