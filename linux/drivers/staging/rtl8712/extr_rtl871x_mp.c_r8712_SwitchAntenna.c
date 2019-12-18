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
typedef  int u32 ;
struct TYPE_2__ {int antenna_tx; int antenna_rx; } ;
struct _adapter {TYPE_1__ mppriv; } ;
struct R_ANTENNA_SELECT_CCK {int r_ccktx_enable; int r_cckrx_enable; int r_cckrx_enable_2; } ;

/* Variables and functions */
#define  ANTENNA_A 130 
#define  ANTENNA_AB 129 
#define  ANTENNA_B 128 
 int bMaskByte3 ; 
 int /*<<< orphan*/  rCCK0_AFESetting ; 
 int /*<<< orphan*/  rFPGA0_TxInfo ; 
 int /*<<< orphan*/  rFPGA0_XA_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XB_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA1_TxInfo ; 
 int /*<<< orphan*/  rOFDM0_TRxPathEnable ; 
 int /*<<< orphan*/  rOFDM1_TRxPathEnable ; 
 int /*<<< orphan*/  set_bb_reg (struct _adapter*,int /*<<< orphan*/ ,int,int) ; 

void r8712_SwitchAntenna(struct _adapter *pAdapter)
{
	u32	ofdm_tx_en_val = 0, ofdm_tx_ant_sel_val = 0;
	u8	ofdm_rx_ant_sel_val = 0;
	u8	cck_ant_select_val = 0;
	u32	cck_ant_sel_val = 0;
	struct R_ANTENNA_SELECT_CCK *p_cck_txrx;

	p_cck_txrx = (struct R_ANTENNA_SELECT_CCK *)&cck_ant_select_val;

	switch (pAdapter->mppriv.antenna_tx) {
	case ANTENNA_A:
		/* From SD3 Willis suggestion !!! Set RF A=TX and B as standby*/
		set_bb_reg(pAdapter, rFPGA0_XA_HSSIParameter2, 0xe, 2);
		set_bb_reg(pAdapter, rFPGA0_XB_HSSIParameter2, 0xe, 1);
		ofdm_tx_en_val = 0x3;
		ofdm_tx_ant_sel_val = 0x11111111;/* Power save */
		p_cck_txrx->r_ccktx_enable = 0x8;
		break;
	case ANTENNA_B:
		set_bb_reg(pAdapter, rFPGA0_XA_HSSIParameter2, 0xe, 1);
		set_bb_reg(pAdapter, rFPGA0_XB_HSSIParameter2, 0xe, 2);
		ofdm_tx_en_val = 0x3;
		ofdm_tx_ant_sel_val = 0x22222222;/* Power save */
		p_cck_txrx->r_ccktx_enable = 0x4;
		break;
	case ANTENNA_AB:	/* For 8192S */
		set_bb_reg(pAdapter, rFPGA0_XA_HSSIParameter2, 0xe, 2);
		set_bb_reg(pAdapter, rFPGA0_XB_HSSIParameter2, 0xe, 2);
		ofdm_tx_en_val = 0x3;
		ofdm_tx_ant_sel_val = 0x3321333; /* Disable Power save */
		p_cck_txrx->r_ccktx_enable = 0xC;
		break;
	default:
		break;
	}
	/*OFDM Tx*/
	set_bb_reg(pAdapter, rFPGA1_TxInfo, 0xffffffff, ofdm_tx_ant_sel_val);
	/*OFDM Tx*/
	set_bb_reg(pAdapter, rFPGA0_TxInfo, 0x0000000f, ofdm_tx_en_val);
	switch (pAdapter->mppriv.antenna_rx) {
	case ANTENNA_A:
		ofdm_rx_ant_sel_val = 0x1;	/* A */
		p_cck_txrx->r_cckrx_enable = 0x0; /* default: A */
		p_cck_txrx->r_cckrx_enable_2 = 0x0; /* option: A */
		break;
	case ANTENNA_B:
		ofdm_rx_ant_sel_val = 0x2;	/* B */
		p_cck_txrx->r_cckrx_enable = 0x1; /* default: B */
		p_cck_txrx->r_cckrx_enable_2 = 0x1; /* option: B */
		break;
	case ANTENNA_AB:
		ofdm_rx_ant_sel_val = 0x3; /* AB */
		p_cck_txrx->r_cckrx_enable = 0x0; /* default:A */
		p_cck_txrx->r_cckrx_enable_2 = 0x1; /* option:B */
		break;
	default:
		break;
	}
	/*OFDM Rx*/
	set_bb_reg(pAdapter, rOFDM0_TRxPathEnable, 0x0000000f,
		   ofdm_rx_ant_sel_val);
	/*OFDM Rx*/
	set_bb_reg(pAdapter, rOFDM1_TRxPathEnable, 0x0000000f,
		   ofdm_rx_ant_sel_val);

	cck_ant_sel_val = cck_ant_select_val;
	/*CCK TxRx*/
	set_bb_reg(pAdapter, rCCK0_AFESetting, bMaskByte3, cck_ant_sel_val);
}