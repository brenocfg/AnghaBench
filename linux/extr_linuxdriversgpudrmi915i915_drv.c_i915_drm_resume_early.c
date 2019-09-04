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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int power_domains_suspended; TYPE_1__ drm; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EIO ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  bxt_disable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_sanitize_dc_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_disable_pc8 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_set_init_power (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_engines_sanitize (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_init_hw (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_uncore_resume_early (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_sanitize (struct drm_i915_private*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int vlv_resume_prepare (struct drm_i915_private*,int) ; 

__attribute__((used)) static int i915_drm_resume_early(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int ret;

	/*
	 * We have a resume ordering issue with the snd-hda driver also
	 * requiring our device to be power up. Due to the lack of a
	 * parent/child relationship we currently solve this with an early
	 * resume hook.
	 *
	 * FIXME: This should be solved with a special hdmi sink device or
	 * similar so that power domains can be employed.
	 */

	/*
	 * Note that we need to set the power state explicitly, since we
	 * powered off the device during freeze and the PCI core won't power
	 * it back up for us during thaw. Powering off the device during
	 * freeze is not a hard requirement though, and during the
	 * suspend/resume phases the PCI core makes sure we get here with the
	 * device powered on. So in case we change our freeze logic and keep
	 * the device powered we can also remove the following set power state
	 * call.
	 */
	ret = pci_set_power_state(pdev, PCI_D0);
	if (ret) {
		DRM_ERROR("failed to set PCI D0 power state (%d)\n", ret);
		goto out;
	}

	/*
	 * Note that pci_enable_device() first enables any parent bridge
	 * device and only then sets the power state for this device. The
	 * bridge enabling is a nop though, since bridge devices are resumed
	 * first. The order of enabling power and enabling the device is
	 * imposed by the PCI core as described above, so here we preserve the
	 * same order for the freeze/thaw phases.
	 *
	 * TODO: eventually we should remove pci_disable_device() /
	 * pci_enable_enable_device() from suspend/resume. Due to how they
	 * depend on the device enable refcount we can't anyway depend on them
	 * disabling/enabling the device.
	 */
	if (pci_enable_device(pdev)) {
		ret = -EIO;
		goto out;
	}

	pci_set_master(pdev);

	disable_rpm_wakeref_asserts(dev_priv);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = vlv_resume_prepare(dev_priv, false);
	if (ret)
		DRM_ERROR("Resume prepare failed: %d, continuing anyway\n",
			  ret);

	intel_uncore_resume_early(dev_priv);

	if (IS_GEN9_LP(dev_priv)) {
		gen9_sanitize_dc_state(dev_priv);
		bxt_disable_dc9(dev_priv);
	} else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		hsw_disable_pc8(dev_priv);
	}

	intel_uncore_sanitize(dev_priv);

	if (dev_priv->power_domains_suspended)
		intel_power_domains_init_hw(dev_priv, true);
	else
		intel_display_set_init_power(dev_priv, true);

	intel_engines_sanitize(dev_priv);

	enable_rpm_wakeref_asserts(dev_priv);

out:
	dev_priv->power_domains_suspended = false;

	return ret;
}