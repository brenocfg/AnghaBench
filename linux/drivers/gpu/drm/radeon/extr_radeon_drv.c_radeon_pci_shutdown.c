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
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ radeon_device_is_virtual () ; 
 int /*<<< orphan*/  radeon_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  radeon_suspend_kms (struct drm_device*,int,int,int) ; 

__attribute__((used)) static void
radeon_pci_shutdown(struct pci_dev *pdev)
{
#ifdef CONFIG_PPC64
	struct drm_device *ddev = pci_get_drvdata(pdev);
#endif

	/* if we are running in a VM, make sure the device
	 * torn down properly on reboot/shutdown
	 */
	if (radeon_device_is_virtual())
		radeon_pci_remove(pdev);

#ifdef CONFIG_PPC64
	/* Some adapters need to be suspended before a
	 * shutdown occurs in order to prevent an error
	 * during kexec.
	 * Make this power specific becauase it breaks
	 * some non-power boards.
	 */
	radeon_suspend_kms(ddev, true, true, false);
#endif
}