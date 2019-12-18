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
typedef  int u32 ;
struct drm_encoder {struct drm_device* dev; } ;
struct TYPE_2__ {struct drm_encoder base; } ;
struct intel_dsi {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int HS_CTRL_FIFO_EMPTY ; 
 int HS_DATA_FIFO_EMPTY ; 
 int LP_CTRL_FIFO_EMPTY ; 
 int LP_DATA_FIFO_EMPTY ; 
 int /*<<< orphan*/  MIPI_GEN_FIFO_STAT (int) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void vlv_dsi_wait_for_fifo_empty(struct intel_dsi *intel_dsi, enum port port)
{
	struct drm_encoder *encoder = &intel_dsi->base.base;
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 mask;

	mask = LP_CTRL_FIFO_EMPTY | HS_CTRL_FIFO_EMPTY |
		LP_DATA_FIFO_EMPTY | HS_DATA_FIFO_EMPTY;

	if (intel_de_wait_for_set(dev_priv, MIPI_GEN_FIFO_STAT(port),
				  mask, 100))
		DRM_ERROR("DPI FIFOs are not empty\n");
}