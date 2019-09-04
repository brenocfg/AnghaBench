#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ vendor; int revision; int /*<<< orphan*/  dev; } ;
struct agp_bridge_data {int /*<<< orphan*/  mode; scalar_t__ capndx; struct pci_dev* dev; int /*<<< orphan*/ * dev_private_data; int /*<<< orphan*/ * driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  chipset_name; } ;
struct TYPE_4__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_ERRATA_1X ; 
 int /*<<< orphan*/  AGP_ERRATA_FASTWRITES ; 
 int /*<<< orphan*/  AGP_ERRATA_SBA ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ PCI_AGP_STATUS ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 int PCI_CLASS_DISPLAY_VGA ; 
 scalar_t__ PCI_DEVICE_ID_AMD_FE_GATE_7006 ; 
 scalar_t__ PCI_DEVICE_ID_AMD_FE_GATE_700E ; 
 scalar_t__ PCI_VENDOR_ID_NVIDIA ; 
 int agp_add_bridge (struct agp_bridge_data*) ; 
 struct agp_bridge_data* agp_alloc_bridge () ; 
 struct pci_device_id const* agp_amdk7_pci_table ; 
 TYPE_3__* agp_bridge ; 
 TYPE_2__* amd_agp_device_ids ; 
 int /*<<< orphan*/  amd_irongate_driver ; 
 int /*<<< orphan*/  amd_irongate_private ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_class (int,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct agp_bridge_data*) ; 

__attribute__((used)) static int agp_amdk7_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct agp_bridge_data *bridge;
	u8 cap_ptr;
	int j;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptr)
		return -ENODEV;

	j = ent - agp_amdk7_pci_table;
	dev_info(&pdev->dev, "AMD %s chipset\n",
		 amd_agp_device_ids[j].chipset_name);

	bridge = agp_alloc_bridge();
	if (!bridge)
		return -ENOMEM;

	bridge->driver = &amd_irongate_driver;
	bridge->dev_private_data = &amd_irongate_private,
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	/* 751 Errata (22564_B-1.PDF)
	   erratum 20: strobe glitch with Nvidia NV10 GeForce cards.
	   system controller may experience noise due to strong drive strengths
	 */
	if (agp_bridge->dev->device == PCI_DEVICE_ID_AMD_FE_GATE_7006) {
		struct pci_dev *gfxcard=NULL;

		cap_ptr = 0;
		while (!cap_ptr) {
			gfxcard = pci_get_class(PCI_CLASS_DISPLAY_VGA<<8, gfxcard);
			if (!gfxcard) {
				dev_info(&pdev->dev, "no AGP VGA controller\n");
				return -ENODEV;
			}
			cap_ptr = pci_find_capability(gfxcard, PCI_CAP_ID_AGP);
		}

		/* With so many variants of NVidia cards, it's simpler just
		   to blacklist them all, and then whitelist them as needed
		   (if necessary at all). */
		if (gfxcard->vendor == PCI_VENDOR_ID_NVIDIA) {
			agp_bridge->flags |= AGP_ERRATA_1X;
			dev_info(&pdev->dev, "AMD 751 chipset with NVidia GeForce; forcing 1X due to errata\n");
		}
		pci_dev_put(gfxcard);
	}

	/* 761 Errata (23613_F.pdf)
	 * Revisions B0/B1 were a disaster.
	 * erratum 44: SYSCLK/AGPCLK skew causes 2X failures -- Force mode to 1X
	 * erratum 45: Timing problem prevents fast writes -- Disable fast write.
	 * erratum 46: Setup violation on AGP SBA pins - Disable side band addressing.
	 * With this lot disabled, we should prevent lockups. */
	if (agp_bridge->dev->device == PCI_DEVICE_ID_AMD_FE_GATE_700E) {
		if (pdev->revision == 0x10 || pdev->revision == 0x11) {
			agp_bridge->flags = AGP_ERRATA_FASTWRITES;
			agp_bridge->flags |= AGP_ERRATA_SBA;
			agp_bridge->flags |= AGP_ERRATA_1X;
			dev_info(&pdev->dev, "AMD 761 chipset with errata; disabling AGP fast writes & SBA and forcing to 1X\n");
		}
	}

	/* Fill in the mode register */
	pci_read_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS,
			&bridge->mode);

	pci_set_drvdata(pdev, bridge);
	return agp_add_bridge(bridge);
}