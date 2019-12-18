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
struct xhci_hcd {int quirks; int hci_version; int limit_active_eps; } ;
struct pci_dev {scalar_t__ vendor; int device; int revision; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PCI_DEVICE_ID_AMD_PROMONTORYA_1 ; 
 int PCI_DEVICE_ID_AMD_PROMONTORYA_2 ; 
 int PCI_DEVICE_ID_AMD_PROMONTORYA_3 ; 
 int PCI_DEVICE_ID_AMD_PROMONTORYA_4 ; 
 int PCI_DEVICE_ID_ASMEDIA_1042A_XHCI ; 
 int PCI_DEVICE_ID_EJ168 ; 
 int PCI_DEVICE_ID_FRESCO_LOGIC_FL1009 ; 
 int PCI_DEVICE_ID_FRESCO_LOGIC_FL1400 ; 
 int PCI_DEVICE_ID_FRESCO_LOGIC_PDK ; 
 int PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_XHCI ; 
 int PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_XHCI ; 
 int PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_XHCI ; 
 int PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_XHCI ; 
 int PCI_DEVICE_ID_INTEL_APL_XHCI ; 
 int PCI_DEVICE_ID_INTEL_BROXTON_B_XHCI ; 
 int PCI_DEVICE_ID_INTEL_BROXTON_M_XHCI ; 
 int PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ; 
 int PCI_DEVICE_ID_INTEL_DNV_XHCI ; 
 int PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_XHCI ; 
 int PCI_DEVICE_ID_INTEL_PANTHERPOINT_XHCI ; 
 int PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_XHCI ; 
 int PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ; 
 int PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_XHCI ; 
 int PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_XHCI ; 
 int PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_XHCI ; 
 int PCI_DEVICE_ID_INTEL_WILDCATPOINT_LP_XHCI ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_ASMEDIA ; 
 scalar_t__ PCI_VENDOR_ID_BROADCOM ; 
 scalar_t__ PCI_VENDOR_ID_CAVIUM ; 
 scalar_t__ PCI_VENDOR_ID_ETRON ; 
 scalar_t__ PCI_VENDOR_ID_FRESCO_LOGIC ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_NEC ; 
 scalar_t__ PCI_VENDOR_ID_RENESAS ; 
 scalar_t__ PCI_VENDOR_ID_TI ; 
 scalar_t__ PCI_VENDOR_ID_VIA ; 
 int XHCI_AMD_0x96_HOST ; 
 int XHCI_AMD_PLL_FIX ; 
 int XHCI_ASMEDIA_MODIFY_FLOWCONTROL ; 
 int XHCI_AVOID_BEI ; 
 int XHCI_BROKEN_MSI ; 
 int XHCI_BROKEN_STREAMS ; 
 int XHCI_DEFAULT_PM_RUNTIME_ALLOW ; 
 int XHCI_EP_LIMIT_QUIRK ; 
 int XHCI_INTEL_HOST ; 
 int XHCI_INTEL_USB_ROLE_SW ; 
 int XHCI_LIMIT_ENDPOINT_INTERVAL_7 ; 
 int XHCI_LPM_SUPPORT ; 
 int XHCI_MISSING_CAS ; 
 int XHCI_NEC_HOST ; 
 int XHCI_PME_STUCK_QUIRK ; 
 int XHCI_RESET_EP_QUIRK ; 
 int XHCI_RESET_ON_RESUME ; 
 int XHCI_RESET_PLL_ON_DISCONNECT ; 
 int XHCI_SLOW_SUSPEND ; 
 int XHCI_SNPS_BROKEN_SUSPEND ; 
 int XHCI_SPURIOUS_REBOOT ; 
 int XHCI_SPURIOUS_WAKEUP ; 
 int XHCI_SSIC_PORT_UNUSED ; 
 int XHCI_SUSPEND_DELAY ; 
 int XHCI_SW_BW_CHECKING ; 
 int XHCI_TRUST_TX_LENGTH ; 
 int XHCI_U2_DISABLE_WAKE ; 
 int XHCI_ZERO_64B_REGS ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 scalar_t__ usb_amd_quirk_pll_check () ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void xhci_pci_quirks(struct device *dev, struct xhci_hcd *xhci)
{
	struct pci_dev		*pdev = to_pci_dev(dev);

	/* Look for vendor-specific quirks */
	if (pdev->vendor == PCI_VENDOR_ID_FRESCO_LOGIC &&
			(pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK ||
			 pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_FL1400)) {
		if (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK &&
				pdev->revision == 0x0) {
			xhci->quirks |= XHCI_RESET_EP_QUIRK;
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Fresco Logic xHC needs configure"
				" endpoint cmd after reset endpoint");
		}
		if (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK &&
				pdev->revision == 0x4) {
			xhci->quirks |= XHCI_SLOW_SUSPEND;
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Fresco Logic xHC revision %u"
				"must be suspended extra slowly",
				pdev->revision);
		}
		if (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK)
			xhci->quirks |= XHCI_BROKEN_STREAMS;
		/* Fresco Logic confirms: all revisions of this chip do not
		 * support MSI, even though some of them claim to in their PCI
		 * capabilities.
		 */
		xhci->quirks |= XHCI_BROKEN_MSI;
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Fresco Logic revision %u "
				"has broken MSI implementation",
				pdev->revision);
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
	}

	if (pdev->vendor == PCI_VENDOR_ID_FRESCO_LOGIC &&
			pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_FL1009)
		xhci->quirks |= XHCI_BROKEN_STREAMS;

	if (pdev->vendor == PCI_VENDOR_ID_NEC)
		xhci->quirks |= XHCI_NEC_HOST;

	if (pdev->vendor == PCI_VENDOR_ID_AMD && xhci->hci_version == 0x96)
		xhci->quirks |= XHCI_AMD_0x96_HOST;

	/* AMD PLL quirk */
	if (pdev->vendor == PCI_VENDOR_ID_AMD && usb_amd_quirk_pll_check())
		xhci->quirks |= XHCI_AMD_PLL_FIX;

	if (pdev->vendor == PCI_VENDOR_ID_AMD &&
		(pdev->device == 0x15e0 ||
		 pdev->device == 0x15e1 ||
		 pdev->device == 0x43bb))
		xhci->quirks |= XHCI_SUSPEND_DELAY;

	if (pdev->vendor == PCI_VENDOR_ID_AMD &&
	    (pdev->device == 0x15e0 || pdev->device == 0x15e1))
		xhci->quirks |= XHCI_SNPS_BROKEN_SUSPEND;

	if (pdev->vendor == PCI_VENDOR_ID_AMD)
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;

	if ((pdev->vendor == PCI_VENDOR_ID_AMD) &&
		((pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_4) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_3) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_2) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_1)))
		xhci->quirks |= XHCI_U2_DISABLE_WAKE;

	if (pdev->vendor == PCI_VENDOR_ID_INTEL) {
		xhci->quirks |= XHCI_LPM_SUPPORT;
		xhci->quirks |= XHCI_INTEL_HOST;
		xhci->quirks |= XHCI_AVOID_BEI;
	}
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
			pdev->device == PCI_DEVICE_ID_INTEL_PANTHERPOINT_XHCI) {
		xhci->quirks |= XHCI_EP_LIMIT_QUIRK;
		xhci->limit_active_eps = 64;
		xhci->quirks |= XHCI_SW_BW_CHECKING;
		/*
		 * PPT desktop boards DH77EB and DH77DF will power back on after
		 * a few seconds of being shutdown.  The fix for this is to
		 * switch the ports from xHCI to EHCI on shutdown.  We can't use
		 * DMI information to find those particular boards (since each
		 * vendor will change the board name), so we have to key off all
		 * PPT chipsets.
		 */
		xhci->quirks |= XHCI_SPURIOUS_REBOOT;
	}
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
		(pdev->device == PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_WILDCATPOINT_LP_XHCI)) {
		xhci->quirks |= XHCI_SPURIOUS_REBOOT;
		xhci->quirks |= XHCI_SPURIOUS_WAKEUP;
	}
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
		(pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_BROXTON_M_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_BROXTON_B_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_APL_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_DNV_XHCI)) {
		xhci->quirks |= XHCI_PME_STUCK_QUIRK;
	}
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI)
		xhci->quirks |= XHCI_SSIC_PORT_UNUSED;
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_APL_XHCI))
		xhci->quirks |= XHCI_INTEL_USB_ROLE_SW;
	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_APL_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_DNV_XHCI))
		xhci->quirks |= XHCI_MISSING_CAS;

	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_XHCI))
		xhci->quirks |= XHCI_DEFAULT_PM_RUNTIME_ALLOW;

	if (pdev->vendor == PCI_VENDOR_ID_ETRON &&
			pdev->device == PCI_DEVICE_ID_EJ168) {
		xhci->quirks |= XHCI_RESET_ON_RESUME;
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
		xhci->quirks |= XHCI_BROKEN_STREAMS;
	}
	if (pdev->vendor == PCI_VENDOR_ID_RENESAS &&
	    pdev->device == 0x0014) {
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
		xhci->quirks |= XHCI_ZERO_64B_REGS;
	}
	if (pdev->vendor == PCI_VENDOR_ID_RENESAS &&
	    pdev->device == 0x0015) {
		xhci->quirks |= XHCI_RESET_ON_RESUME;
		xhci->quirks |= XHCI_ZERO_64B_REGS;
	}
	if (pdev->vendor == PCI_VENDOR_ID_VIA)
		xhci->quirks |= XHCI_RESET_ON_RESUME;

	/* See https://bugzilla.kernel.org/show_bug.cgi?id=79511 */
	if (pdev->vendor == PCI_VENDOR_ID_VIA &&
			pdev->device == 0x3432)
		xhci->quirks |= XHCI_BROKEN_STREAMS;

	if (pdev->vendor == PCI_VENDOR_ID_ASMEDIA &&
			pdev->device == 0x1042)
		xhci->quirks |= XHCI_BROKEN_STREAMS;
	if (pdev->vendor == PCI_VENDOR_ID_ASMEDIA &&
			pdev->device == 0x1142)
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;

	if (pdev->vendor == PCI_VENDOR_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042A_XHCI)
		xhci->quirks |= XHCI_ASMEDIA_MODIFY_FLOWCONTROL;

	if (pdev->vendor == PCI_VENDOR_ID_TI && pdev->device == 0x8241)
		xhci->quirks |= XHCI_LIMIT_ENDPOINT_INTERVAL_7;

	if ((pdev->vendor == PCI_VENDOR_ID_BROADCOM ||
	     pdev->vendor == PCI_VENDOR_ID_CAVIUM) &&
	     pdev->device == 0x9026)
		xhci->quirks |= XHCI_RESET_PLL_ON_DISCONNECT;

	if (xhci->quirks & XHCI_RESET_ON_RESUME)
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Resetting on resume");
}