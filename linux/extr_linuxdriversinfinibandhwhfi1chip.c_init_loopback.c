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
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DC8051_CFG_MODE ; 
 int DISABLE_SELF_GUID_CHECK ; 
 int EINVAL ; 
 scalar_t__ ICODE_FPGA_EMULATION ; 
 scalar_t__ ICODE_FUNCTIONAL_SIMULATOR ; 
 scalar_t__ LOOPBACK_CABLE ; 
 scalar_t__ LOOPBACK_LCB ; 
 scalar_t__ LOOPBACK_SERDES ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,...) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 scalar_t__ loopback ; 
 int quick_linkup ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_loopback(struct hfi1_devdata *dd)
{
	dd_dev_info(dd, "Entering loopback mode\n");

	/* all loopbacks should disable self GUID check */
	write_csr(dd, DC_DC8051_CFG_MODE,
		  (read_csr(dd, DC_DC8051_CFG_MODE) | DISABLE_SELF_GUID_CHECK));

	/*
	 * The simulator has only one loopback option - LCB.  Switch
	 * to that option, which includes quick link up.
	 *
	 * Accept all valid loopback values.
	 */
	if ((dd->icode == ICODE_FUNCTIONAL_SIMULATOR) &&
	    (loopback == LOOPBACK_SERDES || loopback == LOOPBACK_LCB ||
	     loopback == LOOPBACK_CABLE)) {
		loopback = LOOPBACK_LCB;
		quick_linkup = 1;
		return 0;
	}

	/*
	 * SerDes loopback init sequence is handled in set_local_link_attributes
	 */
	if (loopback == LOOPBACK_SERDES)
		return 0;

	/* LCB loopback - handled at poll time */
	if (loopback == LOOPBACK_LCB) {
		quick_linkup = 1; /* LCB is always quick linkup */

		/* not supported in emulation due to emulation RTL changes */
		if (dd->icode == ICODE_FPGA_EMULATION) {
			dd_dev_err(dd,
				   "LCB loopback not supported in emulation\n");
			return -EINVAL;
		}
		return 0;
	}

	/* external cable loopback requires no extra steps */
	if (loopback == LOOPBACK_CABLE)
		return 0;

	dd_dev_err(dd, "Invalid loopback mode %d\n", loopback);
	return -EINVAL;
}