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
struct pci_dev {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_device {int /*<<< orphan*/  mp1_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_MP1_STATE_NONE ; 
 int /*<<< orphan*/  PP_MP1_STATE_UNLOAD ; 
 int /*<<< orphan*/  amdgpu_device_ip_suspend (struct amdgpu_device*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void
amdgpu_pci_shutdown(struct pci_dev *pdev)
{
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct amdgpu_device *adev = dev->dev_private;

	/* if we are running in a VM, make sure the device
	 * torn down properly on reboot/shutdown.
	 * unfortunately we can't detect certain
	 * hypervisors so just do this all the time.
	 */
	adev->mp1_state = PP_MP1_STATE_UNLOAD;
	amdgpu_device_ip_suspend(adev);
	adev->mp1_state = PP_MP1_STATE_NONE;
}