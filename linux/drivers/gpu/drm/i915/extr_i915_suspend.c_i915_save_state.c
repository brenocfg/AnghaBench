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
struct TYPE_3__ {void** saveSWF3; void** saveSWF1; void** saveSWF0; void* saveMI_ARB_STATE; void* saveCACHE_MODE_0; int /*<<< orphan*/  saveGCDGMBUS; } ;
struct drm_i915_private {TYPE_2__ drm; TYPE_1__ regfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int /*<<< orphan*/  GCDGMBUS ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MI_ARB_STATE ; 
 int /*<<< orphan*/  SWF0 (int) ; 
 int /*<<< orphan*/  SWF1 (int) ; 
 int /*<<< orphan*/  SWF3 (int) ; 
 int /*<<< orphan*/  i915_save_display (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i915_save_state(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int i;

	mutex_lock(&dev_priv->drm.struct_mutex);

	i915_save_display(dev_priv);

	if (IS_GEN(dev_priv, 4))
		pci_read_config_word(pdev, GCDGMBUS,
				     &dev_priv->regfile.saveGCDGMBUS);

	/* Cache mode state */
	if (INTEL_GEN(dev_priv) < 7)
		dev_priv->regfile.saveCACHE_MODE_0 = I915_READ(CACHE_MODE_0);

	/* Memory Arbitration state */
	dev_priv->regfile.saveMI_ARB_STATE = I915_READ(MI_ARB_STATE);

	/* Scratch space */
	if (IS_GEN(dev_priv, 2) && IS_MOBILE(dev_priv)) {
		for (i = 0; i < 7; i++) {
			dev_priv->regfile.saveSWF0[i] = I915_READ(SWF0(i));
			dev_priv->regfile.saveSWF1[i] = I915_READ(SWF1(i));
		}
		for (i = 0; i < 3; i++)
			dev_priv->regfile.saveSWF3[i] = I915_READ(SWF3(i));
	} else if (IS_GEN(dev_priv, 2)) {
		for (i = 0; i < 7; i++)
			dev_priv->regfile.saveSWF1[i] = I915_READ(SWF1(i));
	} else if (HAS_GMCH(dev_priv)) {
		for (i = 0; i < 16; i++) {
			dev_priv->regfile.saveSWF0[i] = I915_READ(SWF0(i));
			dev_priv->regfile.saveSWF1[i] = I915_READ(SWF1(i));
		}
		for (i = 0; i < 3; i++)
			dev_priv->regfile.saveSWF3[i] = I915_READ(SWF3(i));
	}

	mutex_unlock(&dev_priv->drm.struct_mutex);

	return 0;
}