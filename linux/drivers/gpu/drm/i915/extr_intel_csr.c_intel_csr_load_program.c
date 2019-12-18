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
typedef  size_t u32 ;
struct TYPE_2__ {size_t* dmc_payload; size_t dmc_fw_size; size_t mmio_count; scalar_t__ dc_state; int /*<<< orphan*/ * mmiodata; int /*<<< orphan*/ * mmioaddr; } ;
struct drm_i915_private {TYPE_1__ csr; int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_PROGRAM (size_t) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HAS_CSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen9_set_dc_state_debugmask (struct drm_i915_private*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void intel_csr_load_program(struct drm_i915_private *dev_priv)
{
	u32 *payload = dev_priv->csr.dmc_payload;
	u32 i, fw_size;

	if (!HAS_CSR(dev_priv)) {
		DRM_ERROR("No CSR support available for this platform\n");
		return;
	}

	if (!dev_priv->csr.dmc_payload) {
		DRM_ERROR("Tried to program CSR with empty payload\n");
		return;
	}

	fw_size = dev_priv->csr.dmc_fw_size;
	assert_rpm_wakelock_held(&dev_priv->runtime_pm);

	preempt_disable();

	for (i = 0; i < fw_size; i++)
		I915_WRITE_FW(CSR_PROGRAM(i), payload[i]);

	preempt_enable();

	for (i = 0; i < dev_priv->csr.mmio_count; i++) {
		I915_WRITE(dev_priv->csr.mmioaddr[i],
			   dev_priv->csr.mmiodata[i]);
	}

	dev_priv->csr.dc_state = 0;

	gen9_set_dc_state_debugmask(dev_priv);
}