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
struct vmw_private {scalar_t__ refuse_hibernation; } ;
struct pci_dev {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

__attribute__((used)) static int vmw_pci_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct vmw_private *dev_priv = vmw_priv(dev);

	if (dev_priv->refuse_hibernation)
		return -EBUSY;

	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, PCI_D3hot);
	return 0;
}