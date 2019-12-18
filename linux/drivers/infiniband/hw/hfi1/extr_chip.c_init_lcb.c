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
 int /*<<< orphan*/  DC_LCB_CFG_CLK_CNTR ; 
 int /*<<< orphan*/  DC_LCB_CFG_CNT_FOR_SKIP_STALL ; 
 int /*<<< orphan*/  DC_LCB_CFG_LANE_WIDTH ; 
 int /*<<< orphan*/  DC_LCB_CFG_LOOPBACK ; 
 int /*<<< orphan*/  DC_LCB_CFG_REINIT_AS_SLAVE ; 
 int /*<<< orphan*/  DC_LCB_CFG_TX_FIFOS_RESET ; 
 scalar_t__ ICODE_FUNCTIONAL_SIMULATOR ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_lcb(struct hfi1_devdata *dd)
{
	/* simulator does not correctly handle LCB cclk loopback, skip */
	if (dd->icode == ICODE_FUNCTIONAL_SIMULATOR)
		return;

	/* the DC has been reset earlier in the driver load */

	/* set LCB for cclk loopback on the port */
	write_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0x01);
	write_csr(dd, DC_LCB_CFG_LANE_WIDTH, 0x00);
	write_csr(dd, DC_LCB_CFG_REINIT_AS_SLAVE, 0x00);
	write_csr(dd, DC_LCB_CFG_CNT_FOR_SKIP_STALL, 0x110);
	write_csr(dd, DC_LCB_CFG_CLK_CNTR, 0x08);
	write_csr(dd, DC_LCB_CFG_LOOPBACK, 0x02);
	write_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET, 0x00);
}