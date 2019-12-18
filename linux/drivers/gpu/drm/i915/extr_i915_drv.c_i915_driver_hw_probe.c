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
struct pci_dev {scalar_t__ msi_enabled; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int /*<<< orphan*/  pm_qos; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ HAS_EXECLISTS (struct drm_i915_private*) ; 
 scalar_t__ HAS_PPGTT (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I965G (struct drm_i915_private*) ; 
 scalar_t__ IS_I965GM (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edram_detect (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_ggtt_driver_release (struct drm_i915_private*) ; 
 int i915_ggtt_enable_hw (struct drm_i915_private*) ; 
 int i915_ggtt_init_hw (struct drm_i915_private*) ; 
 int i915_ggtt_probe_hw (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_probe_failure (struct drm_i915_private*) ; 
 int i915_kick_out_firmware_fb (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_perf_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_report_error (struct drm_i915_private*,char*) ; 
 int /*<<< orphan*/  intel_bw_init_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_device_info_runtime_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_get_dram_info (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_init_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_init_workarounds (struct drm_i915_private*) ; 
 int intel_gvt_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_opregion_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_sanitize_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_sanitize_options (struct drm_i915_private*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_vgpu_has_full_ppgtt (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_vgpu_has_hwsp_emulation (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 scalar_t__ pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int vga_remove_vgacon (struct pci_dev*) ; 

__attribute__((used)) static int i915_driver_hw_probe(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	int ret;

	if (i915_inject_probe_failure(dev_priv))
		return -ENODEV;

	intel_device_info_runtime_init(dev_priv);

	if (HAS_PPGTT(dev_priv)) {
		if (intel_vgpu_active(dev_priv) &&
		    !intel_vgpu_has_full_ppgtt(dev_priv)) {
			i915_report_error(dev_priv,
					  "incompatible vGPU found, support for isolated ppGTT required\n");
			return -ENXIO;
		}
	}

	if (HAS_EXECLISTS(dev_priv)) {
		/*
		 * Older GVT emulation depends upon intercepting CSB mmio,
		 * which we no longer use, preferring to use the HWSP cache
		 * instead.
		 */
		if (intel_vgpu_active(dev_priv) &&
		    !intel_vgpu_has_hwsp_emulation(dev_priv)) {
			i915_report_error(dev_priv,
					  "old vGPU host found, support for HWSP emulation required\n");
			return -ENXIO;
		}
	}

	intel_sanitize_options(dev_priv);

	/* needs to be done before ggtt probe */
	edram_detect(dev_priv);

	i915_perf_init(dev_priv);

	ret = i915_ggtt_probe_hw(dev_priv);
	if (ret)
		goto err_perf;

	/*
	 * WARNING: Apparently we must kick fbdev drivers before vgacon,
	 * otherwise the vga fbdev driver falls over.
	 */
	ret = i915_kick_out_firmware_fb(dev_priv);
	if (ret) {
		DRM_ERROR("failed to remove conflicting framebuffer drivers\n");
		goto err_ggtt;
	}

	ret = vga_remove_vgacon(pdev);
	if (ret) {
		DRM_ERROR("failed to remove conflicting VGA console\n");
		goto err_ggtt;
	}

	ret = i915_ggtt_init_hw(dev_priv);
	if (ret)
		goto err_ggtt;

	intel_gt_init_hw(dev_priv);

	ret = i915_ggtt_enable_hw(dev_priv);
	if (ret) {
		DRM_ERROR("failed to enable GGTT\n");
		goto err_ggtt;
	}

	pci_set_master(pdev);

	/*
	 * We don't have a max segment size, so set it to the max so sg's
	 * debugging layer doesn't complain
	 */
	dma_set_max_seg_size(&pdev->dev, UINT_MAX);

	/* overlay on gen2 is broken and can't address above 1G */
	if (IS_GEN(dev_priv, 2)) {
		ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(30));
		if (ret) {
			DRM_ERROR("failed to set DMA mask\n");

			goto err_ggtt;
		}
	}

	/* 965GM sometimes incorrectly writes to hardware status page (HWS)
	 * using 32bit addressing, overwriting memory if HWS is located
	 * above 4GB.
	 *
	 * The documentation also mentions an issue with undefined
	 * behaviour if any general state is accessed within a page above 4GB,
	 * which also needs to be handled carefully.
	 */
	if (IS_I965G(dev_priv) || IS_I965GM(dev_priv)) {
		ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

		if (ret) {
			DRM_ERROR("failed to set DMA mask\n");

			goto err_ggtt;
		}
	}

	pm_qos_add_request(&dev_priv->pm_qos, PM_QOS_CPU_DMA_LATENCY,
			   PM_QOS_DEFAULT_VALUE);

	/* BIOS often leaves RC6 enabled, but disable it for hw init */
	intel_sanitize_gt_powersave(dev_priv);

	intel_gt_init_workarounds(dev_priv);

	/* On the 945G/GM, the chipset reports the MSI capability on the
	 * integrated graphics even though the support isn't actually there
	 * according to the published specs.  It doesn't appear to function
	 * correctly in testing on 945G.
	 * This may be a side effect of MSI having been made available for PEG
	 * and the registers being closely associated.
	 *
	 * According to chipset errata, on the 965GM, MSI interrupts may
	 * be lost or delayed, and was defeatured. MSI interrupts seem to
	 * get lost on g4x as well, and interrupt delivery seems to stay
	 * properly dead afterwards. So we'll just disable them for all
	 * pre-gen5 chipsets.
	 *
	 * dp aux and gmbus irq on gen4 seems to be able to generate legacy
	 * interrupts even when in MSI mode. This results in spurious
	 * interrupt warnings if the legacy irq no. is shared with another
	 * device. The kernel then disables that interrupt source and so
	 * prevents the other device from working properly.
	 */
	if (INTEL_GEN(dev_priv) >= 5) {
		if (pci_enable_msi(pdev) < 0)
			DRM_DEBUG_DRIVER("can't enable MSI");
	}

	ret = intel_gvt_init(dev_priv);
	if (ret)
		goto err_msi;

	intel_opregion_setup(dev_priv);
	/*
	 * Fill the dram structure to get the system raw bandwidth and
	 * dram info. This will be used for memory latency calculation.
	 */
	intel_get_dram_info(dev_priv);

	intel_bw_init_hw(dev_priv);

	return 0;

err_msi:
	if (pdev->msi_enabled)
		pci_disable_msi(pdev);
	pm_qos_remove_request(&dev_priv->pm_qos);
err_ggtt:
	i915_ggtt_driver_release(dev_priv);
err_perf:
	i915_perf_fini(dev_priv);
	return ret;
}