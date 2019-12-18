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
struct TYPE_4__ {int /*<<< orphan*/ * gpu_info_fw; } ;
struct TYPE_3__ {scalar_t__ mode_config_initialized; } ;
struct amdgpu_device {int shutdown; int accel_working; int flags; scalar_t__ asic_type; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rmmio; int /*<<< orphan*/ * rio_mem; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * bios; int /*<<< orphan*/  delayed_init_work; TYPE_2__ firmware; int /*<<< orphan*/  ddev; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int AMD_IS_PX ; 
 scalar_t__ CHIP_NAVI10 ; 
 int /*<<< orphan*/  CONFIG_PERF_EVENTS ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgim_is_hwperf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_atombios_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_debugfs_preempt_cleanup (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_debugfs_regs_cleanup (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_doorbell_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int amdgpu_device_ip_fini (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_discovery ; 
 int /*<<< orphan*/  amdgpu_discovery_fini (struct amdgpu_device*) ; 
 int amdgpu_emu_mode ; 
 int /*<<< orphan*/  amdgpu_fbdev_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_fence_driver_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_i2c_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_irq_disable_all (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_pm_sysfs_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_pm_virt_sysfs_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_pmu_fini (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ucode_sysfs_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_pcie_replay_count ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_helper_force_disable_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_thunderbolt_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_fini_domain_pm_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (int /*<<< orphan*/ ) ; 

void amdgpu_device_fini(struct amdgpu_device *adev)
{
	int r;

	DRM_INFO("amdgpu: finishing device.\n");
	adev->shutdown = true;
	/* disable all interrupts */
	amdgpu_irq_disable_all(adev);
	if (adev->mode_info.mode_config_initialized){
		if (!amdgpu_device_has_dc_support(adev))
			drm_helper_force_disable_all(adev->ddev);
		else
			drm_atomic_helper_shutdown(adev->ddev);
	}
	amdgpu_fence_driver_fini(adev);
	amdgpu_pm_sysfs_fini(adev);
	amdgpu_fbdev_fini(adev);
	r = amdgpu_device_ip_fini(adev);
	if (adev->firmware.gpu_info_fw) {
		release_firmware(adev->firmware.gpu_info_fw);
		adev->firmware.gpu_info_fw = NULL;
	}
	adev->accel_working = false;
	cancel_delayed_work_sync(&adev->delayed_init_work);
	/* free i2c buses */
	if (!amdgpu_device_has_dc_support(adev))
		amdgpu_i2c_fini(adev);

	if (amdgpu_emu_mode != 1)
		amdgpu_atombios_fini(adev);

	kfree(adev->bios);
	adev->bios = NULL;
	if (!pci_is_thunderbolt_attached(adev->pdev))
		vga_switcheroo_unregister_client(adev->pdev);
	if (adev->flags & AMD_IS_PX)
		vga_switcheroo_fini_domain_pm_ops(adev->dev);
	vga_client_register(adev->pdev, NULL, NULL, NULL);
	if (adev->rio_mem)
		pci_iounmap(adev->pdev, adev->rio_mem);
	adev->rio_mem = NULL;
	iounmap(adev->rmmio);
	adev->rmmio = NULL;
	amdgpu_device_doorbell_fini(adev);
	if (amdgpu_sriov_vf(adev) && amdgim_is_hwperf(adev))
		amdgpu_pm_virt_sysfs_fini(adev);

	amdgpu_debugfs_regs_cleanup(adev);
	device_remove_file(adev->dev, &dev_attr_pcie_replay_count);
	amdgpu_ucode_sysfs_fini(adev);
	if (IS_ENABLED(CONFIG_PERF_EVENTS))
		amdgpu_pmu_fini(adev);
	amdgpu_debugfs_preempt_cleanup(adev);
	if (amdgpu_discovery && adev->asic_type >= CHIP_NAVI10)
		amdgpu_discovery_fini(adev);
}