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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct pci_dev {int dummy; } ;
struct drm_psb_private {scalar_t__ platform_rev_id; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,scalar_t__*) ; 

__attribute__((used)) static void mid_get_pci_revID(struct drm_psb_private *dev_priv)
{
	uint32_t platform_rev_id = 0;
	int domain = pci_domain_nr(dev_priv->dev->pdev->bus);
	struct pci_dev *pci_gfx_root =
		pci_get_domain_bus_and_slot(domain, 0, PCI_DEVFN(2, 0));

	if (pci_gfx_root == NULL) {
		WARN_ON(1);
		return;
	}
	pci_read_config_dword(pci_gfx_root, 0x08, &platform_rev_id);
	dev_priv->platform_rev_id = (uint8_t) platform_rev_id;
	pci_dev_put(pci_gfx_root);
	dev_dbg(dev_priv->dev->dev, "platform_rev_id is %x\n",
					dev_priv->platform_rev_id);
}