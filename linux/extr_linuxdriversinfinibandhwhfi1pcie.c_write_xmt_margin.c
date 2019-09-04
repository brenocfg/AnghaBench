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
typedef  int u64 ;
struct hfi1_devdata {TYPE_1__* pcidev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCE_PCIE_CTRL ; 
 int LANE_BUNDLE_MASK ; 
 int LANE_BUNDLE_SHIFT ; 
 int LANE_DELAY_MASK ; 
 int LANE_DELAY_SHIFT ; 
 int MARGIN_G1_G2_OVERWRITE_MASK ; 
 int MARGIN_G1_G2_OVERWRITE_SHIFT ; 
 int MARGIN_GEN1_GEN2_MASK ; 
 int MARGIN_GEN1_GEN2_SHIFT ; 
 int MARGIN_OVERWRITE_ENABLE_SHIFT ; 
 int MARGIN_SHIFT ; 
 scalar_t__ PCI_DEVICE_ID_INTEL1 ; 
 int /*<<< orphan*/  dd_dev_dbg (struct hfi1_devdata*,char*,char const*,int) ; 
 scalar_t__ is_ax (struct hfi1_devdata*) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_xmt_margin(struct hfi1_devdata *dd, const char *fname)
{
	u64 pcie_ctrl;
	u64 xmt_margin;
	u64 xmt_margin_oe;
	u64 lane_delay;
	u64 lane_bundle;

	pcie_ctrl = read_csr(dd, CCE_PCIE_CTRL);

	/*
	 * For Discrete, use full-swing.
	 *  - PCIe TX defaults to full-swing.
	 *    Leave this register as default.
	 * For Integrated, use half-swing
	 *  - Copy xmt_margin and xmt_margin_oe
	 *    from Gen1/Gen2 to Gen3.
	 */
	if (dd->pcidev->device == PCI_DEVICE_ID_INTEL1) { /* integrated */
		/* extract initial fields */
		xmt_margin = (pcie_ctrl >> MARGIN_GEN1_GEN2_SHIFT)
			      & MARGIN_GEN1_GEN2_MASK;
		xmt_margin_oe = (pcie_ctrl >> MARGIN_G1_G2_OVERWRITE_SHIFT)
				 & MARGIN_G1_G2_OVERWRITE_MASK;
		lane_delay = (pcie_ctrl >> LANE_DELAY_SHIFT) & LANE_DELAY_MASK;
		lane_bundle = (pcie_ctrl >> LANE_BUNDLE_SHIFT)
			       & LANE_BUNDLE_MASK;

		/*
		 * For A0, EFUSE values are not set.  Override with the
		 * correct values.
		 */
		if (is_ax(dd)) {
			/*
			 * xmt_margin and OverwiteEnabel should be the
			 * same for Gen1/Gen2 and Gen3
			 */
			xmt_margin = 0x5;
			xmt_margin_oe = 0x1;
			lane_delay = 0xF; /* Delay 240ns. */
			lane_bundle = 0x0; /* Set to 1 lane. */
		}

		/* overwrite existing values */
		pcie_ctrl = (xmt_margin << MARGIN_GEN1_GEN2_SHIFT)
			| (xmt_margin_oe << MARGIN_G1_G2_OVERWRITE_SHIFT)
			| (xmt_margin << MARGIN_SHIFT)
			| (xmt_margin_oe << MARGIN_OVERWRITE_ENABLE_SHIFT)
			| (lane_delay << LANE_DELAY_SHIFT)
			| (lane_bundle << LANE_BUNDLE_SHIFT);

		write_csr(dd, CCE_PCIE_CTRL, pcie_ctrl);
	}

	dd_dev_dbg(dd, "%s: program XMT margin, CcePcieCtrl 0x%llx\n",
		   fname, pcie_ctrl);
}