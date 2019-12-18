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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int has_tt; TYPE_2__* regs; TYPE_1__ self; } ;
struct pci_dev {int vendor; int device; int revision; int /*<<< orphan*/  dev; } ;
struct ehci_hcd {int big_endian_mmio; int no_selective_suspend; int amd_pll_fix; int use_dummy_qh; int frame_index_bug; int hcs_params; int sbrn; int /*<<< orphan*/  command; int /*<<< orphan*/  has_ppcd; int /*<<< orphan*/  need_io_watchdog; TYPE_2__* debug; TYPE_2__* caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  control; int /*<<< orphan*/  hcs_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PPCEE ; 
 int DBGP_ENABLED ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int /*<<< orphan*/  HCS_DEBUG_PORT (int) ; 
 int HCS_N_CC (int) ; 
 int HCS_N_PCC (int) ; 
 int HCS_N_PORTS (int) ; 
 int /*<<< orphan*/  PCI_CAP_ID_DBG ; 
 int PCI_DEVICE_ID_INTEL_CE4100_USB ; 
 scalar_t__ PCI_DEVICE_ID_STMICRO_USB_HOST ; 
 int PCI_DEVICE_ID_TDI_EHCI ; 
#define  PCI_VENDOR_ID_AMD 136 
#define  PCI_VENDOR_ID_ATI 135 
#define  PCI_VENDOR_ID_INTEL 134 
#define  PCI_VENDOR_ID_NEC 133 
#define  PCI_VENDOR_ID_NETMOS 132 
#define  PCI_VENDOR_ID_NVIDIA 131 
 int PCI_VENDOR_ID_STMICRO ; 
#define  PCI_VENDOR_ID_TDI 130 
#define  PCI_VENDOR_ID_TOSHIBA_2 129 
#define  PCI_VENDOR_ID_VIA 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,int,int,int) ; 
 int /*<<< orphan*/  ehci_info (struct ehci_hcd*,char*,...) ; 
 int ehci_pci_reinit (struct ehci_hcd*,struct pci_dev*) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int ehci_setup (struct usb_hcd*) ; 
 int /*<<< orphan*/  ehci_warn (struct ehci_hcd*,char*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_amd_hang_symptom_quirk () ; 
 int /*<<< orphan*/  usb_amd_quirk_pll_check () ; 

__attribute__((used)) static int ehci_pci_setup(struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	struct pci_dev		*pdev = to_pci_dev(hcd->self.controller);
	u32			temp;
	int			retval;

	ehci->caps = hcd->regs;

	/*
	 * ehci_init() causes memory for DMA transfers to be
	 * allocated.  Thus, any vendor-specific workarounds based on
	 * limiting the type of memory used for DMA transfers must
	 * happen before ehci_setup() is called.
	 *
	 * Most other workarounds can be done either before or after
	 * init and reset; they are located here too.
	 */
	switch (pdev->vendor) {
	case PCI_VENDOR_ID_TOSHIBA_2:
		/* celleb's companion chip */
		if (pdev->device == 0x01b5) {
#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
			ehci->big_endian_mmio = 1;
#else
			ehci_warn(ehci,
				  "unsupported big endian Toshiba quirk\n");
#endif
		}
		break;
	case PCI_VENDOR_ID_NVIDIA:
		/* NVidia reports that certain chips don't handle
		 * QH, ITD, or SITD addresses above 2GB.  (But TD,
		 * data buffer, and periodic schedule are normal.)
		 */
		switch (pdev->device) {
		case 0x003c:	/* MCP04 */
		case 0x005b:	/* CK804 */
		case 0x00d8:	/* CK8 */
		case 0x00e8:	/* CK8S */
			if (pci_set_consistent_dma_mask(pdev,
						DMA_BIT_MASK(31)) < 0)
				ehci_warn(ehci, "can't enable NVidia "
					"workaround for >2GB RAM\n");
			break;

		/* Some NForce2 chips have problems with selective suspend;
		 * fixed in newer silicon.
		 */
		case 0x0068:
			if (pdev->revision < 0xa4)
				ehci->no_selective_suspend = 1;
			break;
		}
		break;
	case PCI_VENDOR_ID_INTEL:
		if (pdev->device == PCI_DEVICE_ID_INTEL_CE4100_USB)
			hcd->has_tt = 1;
		break;
	case PCI_VENDOR_ID_TDI:
		if (pdev->device == PCI_DEVICE_ID_TDI_EHCI)
			hcd->has_tt = 1;
		break;
	case PCI_VENDOR_ID_AMD:
		/* AMD PLL quirk */
		if (usb_amd_quirk_pll_check())
			ehci->amd_pll_fix = 1;
		/* AMD8111 EHCI doesn't work, according to AMD errata */
		if (pdev->device == 0x7463) {
			ehci_info(ehci, "ignoring AMD8111 (errata)\n");
			retval = -EIO;
			goto done;
		}

		/*
		 * EHCI controller on AMD SB700/SB800/Hudson-2/3 platforms may
		 * read/write memory space which does not belong to it when
		 * there is NULL pointer with T-bit set to 1 in the frame list
		 * table. To avoid the issue, the frame list link pointer
		 * should always contain a valid pointer to a inactive qh.
		 */
		if (pdev->device == 0x7808) {
			ehci->use_dummy_qh = 1;
			ehci_info(ehci, "applying AMD SB700/SB800/Hudson-2/3 EHCI dummy qh workaround\n");
		}
		break;
	case PCI_VENDOR_ID_VIA:
		if (pdev->device == 0x3104 && (pdev->revision & 0xf0) == 0x60) {
			u8 tmp;

			/* The VT6212 defaults to a 1 usec EHCI sleep time which
			 * hogs the PCI bus *badly*. Setting bit 5 of 0x4B makes
			 * that sleep time use the conventional 10 usec.
			 */
			pci_read_config_byte(pdev, 0x4b, &tmp);
			if (tmp & 0x20)
				break;
			pci_write_config_byte(pdev, 0x4b, tmp | 0x20);
		}
		break;
	case PCI_VENDOR_ID_ATI:
		/* AMD PLL quirk */
		if (usb_amd_quirk_pll_check())
			ehci->amd_pll_fix = 1;

		/*
		 * EHCI controller on AMD SB700/SB800/Hudson-2/3 platforms may
		 * read/write memory space which does not belong to it when
		 * there is NULL pointer with T-bit set to 1 in the frame list
		 * table. To avoid the issue, the frame list link pointer
		 * should always contain a valid pointer to a inactive qh.
		 */
		if (pdev->device == 0x4396) {
			ehci->use_dummy_qh = 1;
			ehci_info(ehci, "applying AMD SB700/SB800/Hudson-2/3 EHCI dummy qh workaround\n");
		}
		/* SB600 and old version of SB700 have a bug in EHCI controller,
		 * which causes usb devices lose response in some cases.
		 */
		if ((pdev->device == 0x4386 || pdev->device == 0x4396) &&
				usb_amd_hang_symptom_quirk()) {
			u8 tmp;
			ehci_info(ehci, "applying AMD SB600/SB700 USB freeze workaround\n");
			pci_read_config_byte(pdev, 0x53, &tmp);
			pci_write_config_byte(pdev, 0x53, tmp | (1<<3));
		}
		break;
	case PCI_VENDOR_ID_NETMOS:
		/* MosChip frame-index-register bug */
		ehci_info(ehci, "applying MosChip frame-index workaround\n");
		ehci->frame_index_bug = 1;
		break;
	}

	/* optional debug port, normally in the first BAR */
	temp = pci_find_capability(pdev, PCI_CAP_ID_DBG);
	if (temp) {
		pci_read_config_dword(pdev, temp, &temp);
		temp >>= 16;
		if (((temp >> 13) & 7) == 1) {
			u32 hcs_params = ehci_readl(ehci,
						    &ehci->caps->hcs_params);

			temp &= 0x1fff;
			ehci->debug = hcd->regs + temp;
			temp = ehci_readl(ehci, &ehci->debug->control);
			ehci_info(ehci, "debug port %d%s\n",
				  HCS_DEBUG_PORT(hcs_params),
				  (temp & DBGP_ENABLED) ? " IN USE" : "");
			if (!(temp & DBGP_ENABLED))
				ehci->debug = NULL;
		}
	}

	retval = ehci_setup(hcd);
	if (retval)
		return retval;

	/* These workarounds need to be applied after ehci_setup() */
	switch (pdev->vendor) {
	case PCI_VENDOR_ID_NEC:
	case PCI_VENDOR_ID_INTEL:
	case PCI_VENDOR_ID_AMD:
		ehci->need_io_watchdog = 0;
		break;
	case PCI_VENDOR_ID_NVIDIA:
		switch (pdev->device) {
		/* MCP89 chips on the MacBookAir3,1 give EPROTO when
		 * fetching device descriptors unless LPM is disabled.
		 * There are also intermittent problems enumerating
		 * devices with PPCD enabled.
		 */
		case 0x0d9d:
			ehci_info(ehci, "disable ppcd for nvidia mcp89\n");
			ehci->has_ppcd = 0;
			ehci->command &= ~CMD_PPCEE;
			break;
		}
		break;
	}

	/* at least the Genesys GL880S needs fixup here */
	temp = HCS_N_CC(ehci->hcs_params) * HCS_N_PCC(ehci->hcs_params);
	temp &= 0x0f;
	if (temp && HCS_N_PORTS(ehci->hcs_params) > temp) {
		ehci_dbg(ehci, "bogus port configuration: "
			"cc=%d x pcc=%d < ports=%d\n",
			HCS_N_CC(ehci->hcs_params),
			HCS_N_PCC(ehci->hcs_params),
			HCS_N_PORTS(ehci->hcs_params));

		switch (pdev->vendor) {
		case 0x17a0:		/* GENESYS */
			/* GL880S: should be PORTS=2 */
			temp |= (ehci->hcs_params & ~0xf);
			ehci->hcs_params = temp;
			break;
		case PCI_VENDOR_ID_NVIDIA:
			/* NF4: should be PCC=10 */
			break;
		}
	}

	/* Serial Bus Release Number is at PCI 0x60 offset */
	if (pdev->vendor == PCI_VENDOR_ID_STMICRO
	    && pdev->device == PCI_DEVICE_ID_STMICRO_USB_HOST)
		;	/* ConneXT has no sbrn register */
	else
		pci_read_config_byte(pdev, 0x60, &ehci->sbrn);

	/* Keep this around for a while just in case some EHCI
	 * implementation uses legacy PCI PM support.  This test
	 * can be removed on 17 Dec 2009 if the dev_warn() hasn't
	 * been triggered by then.
	 */
	if (!device_can_wakeup(&pdev->dev)) {
		u16	port_wake;

		pci_read_config_word(pdev, 0x62, &port_wake);
		if (port_wake & 0x0001) {
			dev_warn(&pdev->dev, "Enabling legacy PCI PM\n");
			device_set_wakeup_capable(&pdev->dev, 1);
		}
	}

#ifdef	CONFIG_PM
	if (ehci->no_selective_suspend && device_can_wakeup(&pdev->dev))
		ehci_warn(ehci, "selective suspend/wakeup unavailable\n");
#endif

	retval = ehci_pci_reinit(ehci, pdev);
done:
	return retval;
}