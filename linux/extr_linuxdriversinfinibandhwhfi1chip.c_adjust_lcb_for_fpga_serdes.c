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
typedef  int u32 ;
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LCB_CFG_IGNORE_LOST_RCLK ; 
 unsigned long long DC_LCB_CFG_IGNORE_LOST_RCLK_EN_SMASK ; 
 int /*<<< orphan*/  DC_LCB_CFG_LN_DCLK ; 
 int /*<<< orphan*/  DC_LCB_CFG_RX_FIFOS_RADR ; 
 int DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT ; 
 int DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT ; 
 int DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT ; 
 int /*<<< orphan*/  DC_LCB_CFG_TX_FIFOS_RADR ; 
 unsigned long long DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT ; 
 scalar_t__ ICODE_FPGA_EMULATION ; 
 int emulator_rev (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  is_ax (struct hfi1_devdata*) ; 
 scalar_t__ is_emulator_s (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void adjust_lcb_for_fpga_serdes(struct hfi1_devdata *dd)
{
	u64 rx_radr, tx_radr;
	u32 version;

	if (dd->icode != ICODE_FPGA_EMULATION)
		return;

	/*
	 * These LCB defaults on emulator _s are good, nothing to do here:
	 *	LCB_CFG_TX_FIFOS_RADR
	 *	LCB_CFG_RX_FIFOS_RADR
	 *	LCB_CFG_LN_DCLK
	 *	LCB_CFG_IGNORE_LOST_RCLK
	 */
	if (is_emulator_s(dd))
		return;
	/* else this is _p */

	version = emulator_rev(dd);
	if (!is_ax(dd))
		version = 0x2d;	/* all B0 use 0x2d or higher settings */

	if (version <= 0x12) {
		/* release 0x12 and below */

		/*
		 * LCB_CFG_RX_FIFOS_RADR.RST_VAL = 0x9
		 * LCB_CFG_RX_FIFOS_RADR.OK_TO_JUMP_VAL = 0x9
		 * LCB_CFG_RX_FIFOS_RADR.DO_NOT_JUMP_VAL = 0xa
		 */
		rx_radr =
		      0xaull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		/*
		 * LCB_CFG_TX_FIFOS_RADR.ON_REINIT = 0 (default)
		 * LCB_CFG_TX_FIFOS_RADR.RST_VAL = 6
		 */
		tx_radr = 6ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	} else if (version <= 0x18) {
		/* release 0x13 up to 0x18 */
		/* LCB_CFG_RX_FIFOS_RADR = 0x988 */
		rx_radr =
		      0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 7ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	} else if (version == 0x19) {
		/* release 0x19 */
		/* LCB_CFG_RX_FIFOS_RADR = 0xa99 */
		rx_radr =
		      0xAull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 3ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	} else if (version == 0x1a) {
		/* release 0x1a */
		/* LCB_CFG_RX_FIFOS_RADR = 0x988 */
		rx_radr =
		      0x9ull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 7ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
		write_csr(dd, DC_LCB_CFG_LN_DCLK, 1ull);
	} else {
		/* release 0x1b and higher */
		/* LCB_CFG_RX_FIFOS_RADR = 0x877 */
		rx_radr =
		      0x8ull << DC_LCB_CFG_RX_FIFOS_RADR_DO_NOT_JUMP_VAL_SHIFT
		    | 0x7ull << DC_LCB_CFG_RX_FIFOS_RADR_OK_TO_JUMP_VAL_SHIFT
		    | 0x7ull << DC_LCB_CFG_RX_FIFOS_RADR_RST_VAL_SHIFT;
		tx_radr = 3ull << DC_LCB_CFG_TX_FIFOS_RADR_RST_VAL_SHIFT;
	}

	write_csr(dd, DC_LCB_CFG_RX_FIFOS_RADR, rx_radr);
	/* LCB_CFG_IGNORE_LOST_RCLK.EN = 1 */
	write_csr(dd, DC_LCB_CFG_IGNORE_LOST_RCLK,
		  DC_LCB_CFG_IGNORE_LOST_RCLK_EN_SMASK);
	write_csr(dd, DC_LCB_CFG_TX_FIFOS_RADR, tx_radr);
}