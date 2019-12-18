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
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; struct pci_dev* pdev; } ;
struct TYPE_3__ {int saveCACHE_MODE_0; int saveMI_ARB_STATE; int* saveSWF0; int* saveSWF1; int* saveSWF3; int /*<<< orphan*/  saveGCDGMBUS; } ;
struct drm_i915_private {TYPE_2__ drm; TYPE_1__ regfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int /*<<< orphan*/  GCDGMBUS ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MI_ARB_STATE ; 
 int /*<<< orphan*/  SWF0 (int) ; 
 int /*<<< orphan*/  SWF1 (int) ; 
 int /*<<< orphan*/  SWF3 (int) ; 
 int /*<<< orphan*/  i915_restore_display (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gmbus_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i915_restore_state(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int i;

	mutex_lock(&dev_priv->drm.struct_mutex);

	if (IS_GEN(dev_priv, 4))
		pci_write_config_word(pdev, GCDGMBUS,
				      dev_priv->regfile.saveGCDGMBUS);
	i915_restore_display(dev_priv);

	/* Cache mode state */
	if (INTEL_GEN(dev_priv) < 7)
		I915_WRITE(CACHE_MODE_0, dev_priv->regfile.saveCACHE_MODE_0 |
			   0xffff0000);

	/* Memory arbitration state */
	I915_WRITE(MI_ARB_STATE, dev_priv->regfile.saveMI_ARB_STATE | 0xffff0000);

	/* Scratch space */
	if (IS_GEN(dev_priv, 2) && IS_MOBILE(dev_priv)) {
		for (i = 0; i < 7; i++) {
			I915_WRITE(SWF0(i), dev_priv->regfile.saveSWF0[i]);
			I915_WRITE(SWF1(i), dev_priv->regfile.saveSWF1[i]);
		}
		for (i = 0; i < 3; i++)
			I915_WRITE(SWF3(i), dev_priv->regfile.saveSWF3[i]);
	} else if (IS_GEN(dev_priv, 2)) {
		for (i = 0; i < 7; i++)
			I915_WRITE(SWF1(i), dev_priv->regfile.saveSWF1[i]);
	} else if (HAS_GMCH(dev_priv)) {
		for (i = 0; i < 16; i++) {
			I915_WRITE(SWF0(i), dev_priv->regfile.saveSWF0[i]);
			I915_WRITE(SWF1(i), dev_priv->regfile.saveSWF1[i]);
		}
		for (i = 0; i < 3; i++)
			I915_WRITE(SWF3(i), dev_priv->regfile.saveSWF3[i]);
	}

	mutex_unlock(&dev_priv->drm.struct_mutex);

	intel_gmbus_reset(dev_priv);

	return 0;
}