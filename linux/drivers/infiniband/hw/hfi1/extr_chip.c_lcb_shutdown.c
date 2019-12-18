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
typedef  unsigned long long u64 ;
struct hfi1_devdata {unsigned long long lcb_err_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCC_CFG_RESET ; 
 unsigned long long DCC_CFG_RESET_RESET_LCB ; 
 unsigned long long DCC_CFG_RESET_RESET_RX_FPE ; 
 int /*<<< orphan*/  DC_LCB_CFG_RUN ; 
 int /*<<< orphan*/  DC_LCB_CFG_TX_FIFOS_RESET ; 
 unsigned long long DC_LCB_CFG_TX_FIFOS_RESET_VAL_SHIFT ; 
 int /*<<< orphan*/  DC_LCB_ERR_EN ; 
 void* read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void lcb_shutdown(struct hfi1_devdata *dd, int abort)
{
	u64 reg;

	/* clear lcb run: LCB_CFG_RUN.EN = 0 */
	write_csr(dd, DC_LCB_CFG_RUN, 0);
	/* set tx fifo reset: LCB_CFG_TX_FIFOS_RESET.VAL = 1 */
	write_csr(dd, DC_LCB_CFG_TX_FIFOS_RESET,
		  1ull << DC_LCB_CFG_TX_FIFOS_RESET_VAL_SHIFT);
	/* set dcc reset csr: DCC_CFG_RESET.{reset_lcb,reset_rx_fpe} = 1 */
	dd->lcb_err_en = read_csr(dd, DC_LCB_ERR_EN);
	reg = read_csr(dd, DCC_CFG_RESET);
	write_csr(dd, DCC_CFG_RESET, reg |
		  DCC_CFG_RESET_RESET_LCB | DCC_CFG_RESET_RESET_RX_FPE);
	(void)read_csr(dd, DCC_CFG_RESET); /* make sure the write completed */
	if (!abort) {
		udelay(1);    /* must hold for the longer of 16cclks or 20ns */
		write_csr(dd, DCC_CFG_RESET, reg);
		write_csr(dd, DC_LCB_ERR_EN, dd->lcb_err_en);
	}
}