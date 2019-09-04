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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * pci_vtd; } ;
struct sbridge_pvt {TYPE_1__ info; struct pci_dev* pci_ta; struct pci_dev* pci_ras; struct pci_dev* pci_sad1; struct pci_dev* pci_ha; struct pci_dev* pci_sad0; struct pci_dev* pci_ddrio; struct pci_dev** pci_tad; } ;
struct sbridge_dev {int n_devs; int /*<<< orphan*/  bus; struct pci_dev** pdev; } ;
struct pci_dev {int device; int /*<<< orphan*/  devfn; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD0 147 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD1 146 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO0 145 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO1 144 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO2 143 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO3 142 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0 141 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TA 140 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD0 139 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD1 138 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD2 137 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD3 136 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TM 135 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1 134 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TA 133 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD0 132 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD1 131 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD2 130 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD3 129 
#define  PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TM 128 
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_HASWELL_IMC_VTD_MISC ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int TAD_DEV_TO_CHAN (int) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/ * pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbridge_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int haswell_mci_bind_devs(struct mem_ctl_info *mci,
				 struct sbridge_dev *sbridge_dev)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	struct pci_dev *pdev;
	u8 saw_chan_mask = 0;
	int i;

	/* there's only one device per system; not tied to any bus */
	if (pvt->info.pci_vtd == NULL)
		/* result will be checked later */
		pvt->info.pci_vtd = pci_get_device(PCI_VENDOR_ID_INTEL,
						   PCI_DEVICE_ID_INTEL_HASWELL_IMC_VTD_MISC,
						   NULL);

	for (i = 0; i < sbridge_dev->n_devs; i++) {
		pdev = sbridge_dev->pdev[i];
		if (!pdev)
			continue;

		switch (pdev->device) {
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD0:
			pvt->pci_sad0 = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_CBO_SAD1:
			pvt->pci_sad1 = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1:
			pvt->pci_ha = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TA:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TA:
			pvt->pci_ta = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TM:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TM:
			pvt->pci_ras = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD0:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD1:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD2:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA0_TAD3:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD0:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD1:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD2:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_HA1_TAD3:
		{
			int id = TAD_DEV_TO_CHAN(pdev->device);
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		}
			break;
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO0:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO1:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO2:
		case PCI_DEVICE_ID_INTEL_HASWELL_IMC_DDRIO3:
			if (!pvt->pci_ddrio)
				pvt->pci_ddrio = pdev;
			break;
		default:
			break;
		}

		edac_dbg(0, "Associated PCI %02x.%02d.%d with dev = %p\n",
			 sbridge_dev->bus,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			 pdev);
	}

	/* Check if everything were registered */
	if (!pvt->pci_sad0 || !pvt->pci_ha || !pvt->pci_sad1 ||
	    !pvt->pci_ras  || !pvt->pci_ta || !pvt->info.pci_vtd)
		goto enodev;

	if (saw_chan_mask != 0x0f && /* -EN/-EX */
	    saw_chan_mask != 0x03)   /* -EP */
		goto enodev;
	return 0;

enodev:
	sbridge_printk(KERN_ERR, "Some needed devices are missing\n");
	return -ENODEV;
}