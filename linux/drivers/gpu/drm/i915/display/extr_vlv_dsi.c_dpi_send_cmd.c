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
typedef  int /*<<< orphan*/  u32 ;
struct drm_encoder {struct drm_device* dev; } ;
struct TYPE_2__ {struct drm_encoder base; } ;
struct intel_dsi {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_LP_MODE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPI_DPI_CONTROL (int) ; 
 int /*<<< orphan*/  MIPI_INTR_STAT (int) ; 
 int /*<<< orphan*/  SPL_PKT_SENT_INTERRUPT ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int dpi_send_cmd(struct intel_dsi *intel_dsi, u32 cmd, bool hs,
			enum port port)
{
	struct drm_encoder *encoder = &intel_dsi->base.base;
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 mask;

	/* XXX: pipe, hs */
	if (hs)
		cmd &= ~DPI_LP_MODE;
	else
		cmd |= DPI_LP_MODE;

	/* clear bit */
	I915_WRITE(MIPI_INTR_STAT(port), SPL_PKT_SENT_INTERRUPT);

	/* XXX: old code skips write if control unchanged */
	if (cmd == I915_READ(MIPI_DPI_CONTROL(port)))
		DRM_DEBUG_KMS("Same special packet %02x twice in a row.\n", cmd);

	I915_WRITE(MIPI_DPI_CONTROL(port), cmd);

	mask = SPL_PKT_SENT_INTERRUPT;
	if (intel_de_wait_for_set(dev_priv, MIPI_INTR_STAT(port), mask, 100))
		DRM_ERROR("Video mode command 0x%08x send failed.\n", cmd);

	return 0;
}