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
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int BIT_CBUS_CMD_ABORT ; 
 int BIT_CBUS_HPD_CHG ; 
 int BIT_CBUS_MHL12_DISCON_INT ; 
 int BIT_CBUS_MHL3_DISCON_INT ; 
 int BIT_CBUS_MSC_ABORT_RCVD ; 
 int BIT_CBUS_MSC_MR_MSC_MSG ; 
 int BIT_CBUS_MSC_MR_SET_INT ; 
 int BIT_CBUS_MSC_MR_WRITE_BURST ; 
 int BIT_CBUS_MSC_MR_WRITE_STAT ; 
 int BIT_CBUS_MSC_MT_DONE ; 
 int BIT_CBUS_MSC_MT_DONE_NACK ; 
 int BIT_COC_CALIBRATION_DONE ; 
 int BIT_COC_PLL_LOCK_STATUS_CHANGE ; 
 int BIT_DISC_CTRL9_DISC_PULSE_PROCEED ; 
 int BIT_DISC_CTRL9_WAKE_DRVFLT ; 
 int BIT_DPD_OSC_EN ; 
 int BIT_DPD_PDNTX12 ; 
 int BIT_DPD_PWRON_HSIC ; 
 int BIT_DPD_PWRON_PLL ; 
 int BIT_MHL3_EST_INT ; 
 int BIT_MHL_DP_CTL0_DP_OE ; 
 int BIT_MHL_DP_CTL0_TX_OE_OVR ; 
 int BIT_MHL_EST_INT ; 
 int BIT_MHL_PLL_CTL0_CRYSTAL_CLK_SEL ; 
 int BIT_MHL_PLL_CTL0_ZONE_MASK_OE ; 
 int BIT_NOT_MHL_EST_INT ; 
 int BIT_RGND_READY_INT ; 
 int /*<<< orphan*/  REG_CBUS_DISC_INTR0_MASK ; 
 int /*<<< orphan*/  REG_CBUS_INT_0_MASK ; 
 int /*<<< orphan*/  REG_CBUS_INT_1_MASK ; 
 int /*<<< orphan*/  REG_COC_CTLC ; 
 int /*<<< orphan*/  REG_COC_INTR_MASK ; 
 int /*<<< orphan*/  REG_DISC_CTRL4 ; 
 int /*<<< orphan*/  REG_DISC_CTRL9 ; 
 int /*<<< orphan*/  REG_DPD ; 
 int /*<<< orphan*/  REG_M3_CTRL ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL0 ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL1 ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL2 ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL3 ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL5 ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL6 ; 
 int /*<<< orphan*/  REG_MHL_DP_CTL7 ; 
 int /*<<< orphan*/  REG_MHL_PLL_CTL0 ; 
 int /*<<< orphan*/  VAL_DISC_CTRL4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAL_M3_CTRL_MHL3_VALUE ; 
 int VAL_MHL_PLL_CTL0_HDMI_CLK_RATIO_1X ; 
 int /*<<< orphan*/  VAL_PUP_20K ; 
 int /*<<< orphan*/  VAL_PUP_5K ; 
 int /*<<< orphan*/  sii8620_write_seq_static (struct sii8620*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_mhl_discover(struct sii8620 *ctx)
{
	sii8620_write_seq_static(ctx,
		REG_DISC_CTRL9, BIT_DISC_CTRL9_WAKE_DRVFLT
			| BIT_DISC_CTRL9_DISC_PULSE_PROCEED,
		REG_DISC_CTRL4, VAL_DISC_CTRL4(VAL_PUP_5K, VAL_PUP_20K),
		REG_CBUS_DISC_INTR0_MASK, BIT_MHL3_EST_INT
			| BIT_MHL_EST_INT
			| BIT_NOT_MHL_EST_INT
			| BIT_CBUS_MHL3_DISCON_INT
			| BIT_CBUS_MHL12_DISCON_INT
			| BIT_RGND_READY_INT,
		REG_MHL_PLL_CTL0, VAL_MHL_PLL_CTL0_HDMI_CLK_RATIO_1X
			| BIT_MHL_PLL_CTL0_CRYSTAL_CLK_SEL
			| BIT_MHL_PLL_CTL0_ZONE_MASK_OE,
		REG_MHL_DP_CTL0, BIT_MHL_DP_CTL0_DP_OE
			| BIT_MHL_DP_CTL0_TX_OE_OVR,
		REG_M3_CTRL, VAL_M3_CTRL_MHL3_VALUE,
		REG_MHL_DP_CTL1, 0xA2,
		REG_MHL_DP_CTL2, 0x03,
		REG_MHL_DP_CTL3, 0x35,
		REG_MHL_DP_CTL5, 0x02,
		REG_MHL_DP_CTL6, 0x02,
		REG_MHL_DP_CTL7, 0x03,
		REG_COC_CTLC, 0xFF,
		REG_DPD, BIT_DPD_PWRON_PLL | BIT_DPD_PDNTX12
			| BIT_DPD_OSC_EN | BIT_DPD_PWRON_HSIC,
		REG_COC_INTR_MASK, BIT_COC_PLL_LOCK_STATUS_CHANGE
			| BIT_COC_CALIBRATION_DONE,
		REG_CBUS_INT_1_MASK, BIT_CBUS_MSC_ABORT_RCVD
			| BIT_CBUS_CMD_ABORT,
		REG_CBUS_INT_0_MASK, BIT_CBUS_MSC_MT_DONE
			| BIT_CBUS_HPD_CHG
			| BIT_CBUS_MSC_MR_WRITE_STAT
			| BIT_CBUS_MSC_MR_MSC_MSG
			| BIT_CBUS_MSC_MR_WRITE_BURST
			| BIT_CBUS_MSC_MR_SET_INT
			| BIT_CBUS_MSC_MT_DONE_NACK
	);
}