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
struct pci_dev {int device; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  topo; struct pci_dev* pdev; } ;
struct intel_ntb_dev {int bar4_split; TYPE_1__ ntb; int /*<<< orphan*/ * reg; int /*<<< orphan*/  hwerr_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ HSX_SPLIT_BAR_MW_COUNT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  NTB_HWERR_B2BDOORBELL_BIT14 ; 
 int /*<<< orphan*/  NTB_HWERR_SB01BASE_LOCKUP ; 
 int /*<<< orphan*/  NTB_HWERR_SDOORBELL_LOCKUP ; 
 int /*<<< orphan*/  NTB_TOPO_NONE ; 
 int /*<<< orphan*/  NTB_TOPO_SEC ; 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_BDX 142 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_HSX 141 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_IVT 140 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_JSF 139 
#define  PCI_DEVICE_ID_INTEL_NTB_B2B_SNB 138 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_BDX 137 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_HSX 136 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_IVT 135 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_JSF 134 
#define  PCI_DEVICE_ID_INTEL_NTB_PS_SNB 133 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_BDX 132 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_HSX 131 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_IVT 130 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_JSF 129 
#define  PCI_DEVICE_ID_INTEL_NTB_SS_SNB 128 
 int /*<<< orphan*/  XEON_PPD_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ hweight32 (int) ; 
 int ntb_topo_string (int /*<<< orphan*/ ) ; 
 int pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int xeon_init_isr (struct intel_ntb_dev*) ; 
 int xeon_init_ntb (struct intel_ntb_dev*) ; 
 int xeon_ppd_bar4_split (struct intel_ntb_dev*,int) ; 
 int /*<<< orphan*/  xeon_ppd_topo (struct intel_ntb_dev*,int) ; 
 int /*<<< orphan*/  xeon_reg ; 

__attribute__((used)) static int xeon_init_dev(struct intel_ntb_dev *ndev)
{
	struct pci_dev *pdev;
	u8 ppd;
	int rc, mem;

	pdev = ndev->ntb.pdev;

	switch (pdev->device) {
	/* There is a Xeon hardware errata related to writes to SDOORBELL or
	 * B2BDOORBELL in conjunction with inbound access to NTB MMIO Space,
	 * which may hang the system.  To workaround this use the second memory
	 * window to access the interrupt and scratch pad registers on the
	 * remote system.
	 */
	case PCI_DEVICE_ID_INTEL_NTB_SS_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_PS_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_SS_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_PS_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		ndev->hwerr_flags |= NTB_HWERR_SDOORBELL_LOCKUP;
		break;
	}

	switch (pdev->device) {
	/* There is a hardware errata related to accessing any register in
	 * SB01BASE in the presence of bidirectional traffic crossing the NTB.
	 */
	case PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		ndev->hwerr_flags |= NTB_HWERR_SB01BASE_LOCKUP;
		break;
	}

	switch (pdev->device) {
	/* HW Errata on bit 14 of b2bdoorbell register.  Writes will not be
	 * mirrored to the remote system.  Shrink the number of bits by one,
	 * since bit 14 is the last bit.
	 */
	case PCI_DEVICE_ID_INTEL_NTB_SS_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_PS_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_JSF:
	case PCI_DEVICE_ID_INTEL_NTB_SS_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_PS_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_SNB:
	case PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		ndev->hwerr_flags |= NTB_HWERR_B2BDOORBELL_BIT14;
		break;
	}

	ndev->reg = &xeon_reg;

	rc = pci_read_config_byte(pdev, XEON_PPD_OFFSET, &ppd);
	if (rc)
		return -EIO;

	ndev->ntb.topo = xeon_ppd_topo(ndev, ppd);
	dev_dbg(&pdev->dev, "ppd %#x topo %s\n", ppd,
		ntb_topo_string(ndev->ntb.topo));
	if (ndev->ntb.topo == NTB_TOPO_NONE)
		return -EINVAL;

	if (ndev->ntb.topo != NTB_TOPO_SEC) {
		ndev->bar4_split = xeon_ppd_bar4_split(ndev, ppd);
		dev_dbg(&pdev->dev, "ppd %#x bar4_split %d\n",
			ppd, ndev->bar4_split);
	} else {
		/* This is a way for transparent BAR to figure out if we are
		 * doing split BAR or not. There is no way for the hw on the
		 * transparent side to know and set the PPD.
		 */
		mem = pci_select_bars(pdev, IORESOURCE_MEM);
		ndev->bar4_split = hweight32(mem) ==
			HSX_SPLIT_BAR_MW_COUNT + 1;
		dev_dbg(&pdev->dev, "mem %#x bar4_split %d\n",
			mem, ndev->bar4_split);
	}

	rc = xeon_init_ntb(ndev);
	if (rc)
		return rc;

	return xeon_init_isr(ndev);
}