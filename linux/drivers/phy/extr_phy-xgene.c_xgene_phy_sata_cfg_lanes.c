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
typedef  int u32 ;
struct TYPE_2__ {int* speed; int /*<<< orphan*/ * txeyetuning; int /*<<< orphan*/ * txeyedirection; int /*<<< orphan*/ * txamplitude; int /*<<< orphan*/ * txprecursor_cn2; int /*<<< orphan*/ * txpostcursor_cp1; int /*<<< orphan*/ * txprecursor_cn1; int /*<<< orphan*/ * txboostgain; } ;
struct xgene_phy_ctx {TYPE_1__ sata_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMU_REG9_WORD_LEN_20BIT ; 
 int MAX_LANE ; 
 int RXTX_REG0 ; 
 int RXTX_REG0_CTLE_EQ_FR_SET (int,int) ; 
 int RXTX_REG0_CTLE_EQ_HR_SET (int,int) ; 
 int RXTX_REG0_CTLE_EQ_QR_SET (int,int) ; 
 int RXTX_REG1 ; 
 int RXTX_REG102 ; 
 int RXTX_REG102_FREQLOOP_LIMIT_SET (int,int) ; 
 int RXTX_REG11 ; 
 int RXTX_REG114 ; 
 int RXTX_REG11_PHASE_ADJUST_LIMIT_SET (int,int) ; 
 int RXTX_REG12 ; 
 int RXTX_REG125 ; 
 int RXTX_REG125_PHZ_MANUAL_SET (int,int) ; 
 int RXTX_REG125_PQ_REG_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG125_SIGN_PQ_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG127 ; 
 int RXTX_REG127_LATCH_MAN_CAL_ENA_SET (int,int) ; 
 int RXTX_REG128 ; 
 int RXTX_REG128_LATCH_CAL_WAIT_SEL_SET (int,int) ; 
 int RXTX_REG12_LATCH_OFF_ENA_SET (int,int) ; 
 int RXTX_REG12_RX_DET_TERM_ENABLE_SET (int,int) ; 
 int RXTX_REG12_SUMOS_ENABLE_SET (int,int) ; 
 int RXTX_REG145 ; 
 int RXTX_REG145_RXDFE_CONFIG_SET (int,int) ; 
 int RXTX_REG145_RXES_ENA_SET (int,int) ; 
 int RXTX_REG145_RXVWES_LATENA_SET (int,int) ; 
 int RXTX_REG145_TX_IDLE_SATA_SET (int,int) ; 
 int RXTX_REG147 ; 
 int RXTX_REG148 ; 
 int RXTX_REG1_CTLE_EQ_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG1_RXACVCM_SET (int,int) ; 
 int RXTX_REG1_RXIREF_ADJ_SET (int,int) ; 
 int RXTX_REG1_RXVREG1_SET (int,int) ; 
 int RXTX_REG2 ; 
 int RXTX_REG26 ; 
 int RXTX_REG26_BLWC_ENA_SET (int,int) ; 
 int RXTX_REG26_PERIOD_ERROR_LATCH_SET (int,int) ; 
 int RXTX_REG28 ; 
 int RXTX_REG2_TX_FIFO_ENA_SET (int,int) ; 
 int RXTX_REG2_VTT_ENA_SET (int,int) ; 
 int RXTX_REG2_VTT_SEL_SET (int,int) ; 
 int RXTX_REG31 ; 
 int RXTX_REG4 ; 
 int RXTX_REG4_TX_WORD_MODE_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG5 ; 
 int RXTX_REG5_TX_CN1_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG5_TX_CN2_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG5_TX_CP1_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG6 ; 
 int RXTX_REG61 ; 
 int RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET (int,int) ; 
 int RXTX_REG61_ISCAN_INBERT_SET (int,int) ; 
 int RXTX_REG61_LOADFREQ_SHIFT_SET (int,int) ; 
 int RXTX_REG62 ; 
 int RXTX_REG62_PERIOD_H1_QLATCH_SET (int,int) ; 
 int RXTX_REG6_RX_BIST_ERRCNT_RD_SET (int,int) ; 
 int RXTX_REG6_RX_BIST_RESYNC_SET (int,int) ; 
 int RXTX_REG6_TXAMP_CNTL_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG6_TXAMP_ENA_SET (int,int) ; 
 int RXTX_REG6_TX_IDLE_SET (int,int) ; 
 int RXTX_REG7 ; 
 int RXTX_REG7_BIST_ENA_RX_SET (int,int) ; 
 int RXTX_REG7_RX_WORD_MODE_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG8 ; 
 int RXTX_REG81 ; 
 int RXTX_REG89_MU_TH7_SET (int,int) ; 
 int RXTX_REG89_MU_TH8_SET (int,int) ; 
 int RXTX_REG89_MU_TH9_SET (int,int) ; 
 int RXTX_REG8_CDR_BYPASS_RXLOS_SET (int,int) ; 
 int RXTX_REG8_CDR_LOOP_ENA_SET (int,int) ; 
 int RXTX_REG8_SD_DISABLE_SET (int,int) ; 
 int RXTX_REG8_SD_VREF_SET (int,int) ; 
 int RXTX_REG8_SSC_ENABLE_SET (int,int) ; 
 int RXTX_REG96 ; 
 int RXTX_REG96_MU_FREQ1_SET (int,int) ; 
 int RXTX_REG96_MU_FREQ2_SET (int,int) ; 
 int RXTX_REG96_MU_FREQ3_SET (int,int) ; 
 int RXTX_REG99 ; 
 int RXTX_REG99_MU_PHASE1_SET (int,int) ; 
 int RXTX_REG99_MU_PHASE2_SET (int,int) ; 
 int RXTX_REG99_MU_PHASE3_SET (int,int) ; 
 scalar_t__ preA3Chip ; 
 int /*<<< orphan*/  serdes_rd (struct xgene_phy_ctx*,int,int,int*) ; 
 int /*<<< orphan*/  serdes_wr (struct xgene_phy_ctx*,int,int,int) ; 

__attribute__((used)) static void xgene_phy_sata_cfg_lanes(struct xgene_phy_ctx *ctx)
{
	u32 val;
	u32 reg;
	int i;
	int lane;

	for (lane = 0; lane < MAX_LANE; lane++) {
		serdes_wr(ctx, lane, RXTX_REG147, 0x6);

		/* Set boost control for quarter, half, and full rate */
		serdes_rd(ctx, lane, RXTX_REG0, &val);
		val = RXTX_REG0_CTLE_EQ_HR_SET(val, 0x10);
		val = RXTX_REG0_CTLE_EQ_QR_SET(val, 0x10);
		val = RXTX_REG0_CTLE_EQ_FR_SET(val, 0x10);
		serdes_wr(ctx, lane, RXTX_REG0, val);

		/* Set boost control value */
		serdes_rd(ctx, lane, RXTX_REG1, &val);
		val = RXTX_REG1_RXACVCM_SET(val, 0x7);
		val = RXTX_REG1_CTLE_EQ_SET(val,
			ctx->sata_param.txboostgain[lane * 3 +
			ctx->sata_param.speed[lane]]);
		serdes_wr(ctx, lane, RXTX_REG1, val);

		/* Latch VTT value based on the termination to ground and
		   enable TX FIFO */
		serdes_rd(ctx, lane, RXTX_REG2, &val);
		val = RXTX_REG2_VTT_ENA_SET(val, 0x1);
		val = RXTX_REG2_VTT_SEL_SET(val, 0x1);
		val = RXTX_REG2_TX_FIFO_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG2, val);

		/* Configure Tx for 20-bits */
		serdes_rd(ctx, lane, RXTX_REG4, &val);
		val = RXTX_REG4_TX_WORD_MODE_SET(val, CMU_REG9_WORD_LEN_20BIT);
		serdes_wr(ctx, lane, RXTX_REG4, val);

		if (!preA3Chip) {
			serdes_rd(ctx, lane, RXTX_REG1, &val);
			val = RXTX_REG1_RXVREG1_SET(val, 0x2);
			val = RXTX_REG1_RXIREF_ADJ_SET(val, 0x2);
			serdes_wr(ctx, lane, RXTX_REG1, val);
		}

		/* Set pre-emphasis first 1 and 2, and post-emphasis values */
		serdes_rd(ctx, lane, RXTX_REG5, &val);
		val = RXTX_REG5_TX_CN1_SET(val,
			ctx->sata_param.txprecursor_cn1[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG5_TX_CP1_SET(val,
			ctx->sata_param.txpostcursor_cp1[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG5_TX_CN2_SET(val,
			ctx->sata_param.txprecursor_cn2[lane * 3 +
			ctx->sata_param.speed[lane]]);
		serdes_wr(ctx, lane, RXTX_REG5, val);

		/* Set TX amplitude value */
		serdes_rd(ctx, lane, RXTX_REG6, &val);
		val = RXTX_REG6_TXAMP_CNTL_SET(val,
			ctx->sata_param.txamplitude[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG6_TXAMP_ENA_SET(val, 0x1);
		val = RXTX_REG6_TX_IDLE_SET(val, 0x0);
		val = RXTX_REG6_RX_BIST_RESYNC_SET(val, 0x0);
		val = RXTX_REG6_RX_BIST_ERRCNT_RD_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG6, val);

		/* Configure Rx for 20-bits */
		serdes_rd(ctx, lane, RXTX_REG7, &val);
		val = RXTX_REG7_BIST_ENA_RX_SET(val, 0x0);
		val = RXTX_REG7_RX_WORD_MODE_SET(val, CMU_REG9_WORD_LEN_20BIT);
		serdes_wr(ctx, lane, RXTX_REG7, val);

		/* Set CDR and LOS values and enable Rx SSC */
		serdes_rd(ctx, lane, RXTX_REG8, &val);
		val = RXTX_REG8_CDR_LOOP_ENA_SET(val, 0x1);
		val = RXTX_REG8_CDR_BYPASS_RXLOS_SET(val, 0x0);
		val = RXTX_REG8_SSC_ENABLE_SET(val, 0x1);
		val = RXTX_REG8_SD_DISABLE_SET(val, 0x0);
		val = RXTX_REG8_SD_VREF_SET(val, 0x4);
		serdes_wr(ctx, lane, RXTX_REG8, val);

		/* Set phase adjust upper/lower limits */
		serdes_rd(ctx, lane, RXTX_REG11, &val);
		val = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG11, val);

		/* Enable Latch Off; disable SUMOS and Tx termination */
		serdes_rd(ctx, lane, RXTX_REG12, &val);
		val = RXTX_REG12_LATCH_OFF_ENA_SET(val, 0x1);
		val = RXTX_REG12_SUMOS_ENABLE_SET(val, 0x0);
		val = RXTX_REG12_RX_DET_TERM_ENABLE_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG12, val);

		/* Set period error latch to 512T and enable BWL */
		serdes_rd(ctx, lane, RXTX_REG26, &val);
		val = RXTX_REG26_PERIOD_ERROR_LATCH_SET(val, 0x0);
		val = RXTX_REG26_BLWC_ENA_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG26, val);

		serdes_wr(ctx, lane, RXTX_REG28, 0x0);

		/* Set DFE loop preset value */
		serdes_wr(ctx, lane, RXTX_REG31, 0x0);

		/* Set Eye Monitor counter width to 12-bit */
		serdes_rd(ctx, lane, RXTX_REG61, &val);
		val = RXTX_REG61_ISCAN_INBERT_SET(val, 0x1);
		val = RXTX_REG61_LOADFREQ_SHIFT_SET(val, 0x0);
		val = RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG61, val);

		serdes_rd(ctx, lane, RXTX_REG62, &val);
		val = RXTX_REG62_PERIOD_H1_QLATCH_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG62, val);

		/* Set BW select tap X for DFE loop */
		for (i = 0; i < 9; i++) {
			reg = RXTX_REG81 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG89_MU_TH7_SET(val, 0xe);
			val = RXTX_REG89_MU_TH8_SET(val, 0xe);
			val = RXTX_REG89_MU_TH9_SET(val, 0xe);
			serdes_wr(ctx, lane, reg, val);
		}

		/* Set BW select tap X for frequency adjust loop */
		for (i = 0; i < 3; i++) {
			reg = RXTX_REG96 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG96_MU_FREQ1_SET(val, 0x10);
			val = RXTX_REG96_MU_FREQ2_SET(val, 0x10);
			val = RXTX_REG96_MU_FREQ3_SET(val, 0x10);
			serdes_wr(ctx, lane, reg, val);
		}

		/* Set BW select tap X for phase adjust loop */
		for (i = 0; i < 3; i++) {
			reg = RXTX_REG99 + i * 2;
			serdes_rd(ctx, lane, reg, &val);
			val = RXTX_REG99_MU_PHASE1_SET(val, 0x7);
			val = RXTX_REG99_MU_PHASE2_SET(val, 0x7);
			val = RXTX_REG99_MU_PHASE3_SET(val, 0x7);
			serdes_wr(ctx, lane, reg, val);
		}

		serdes_rd(ctx, lane, RXTX_REG102, &val);
		val = RXTX_REG102_FREQLOOP_LIMIT_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG102, val);

		serdes_wr(ctx, lane, RXTX_REG114, 0xffe0);

		serdes_rd(ctx, lane, RXTX_REG125, &val);
		val = RXTX_REG125_SIGN_PQ_SET(val,
			ctx->sata_param.txeyedirection[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG125_PQ_REG_SET(val,
			ctx->sata_param.txeyetuning[lane * 3 +
			ctx->sata_param.speed[lane]]);
		val = RXTX_REG125_PHZ_MANUAL_SET(val, 0x1);
		serdes_wr(ctx, lane, RXTX_REG125, val);

		serdes_rd(ctx, lane, RXTX_REG127, &val);
		val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x0);
		serdes_wr(ctx, lane, RXTX_REG127, val);

		serdes_rd(ctx, lane, RXTX_REG128, &val);
		val = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(val, 0x3);
		serdes_wr(ctx, lane, RXTX_REG128, val);

		serdes_rd(ctx, lane, RXTX_REG145, &val);
		val = RXTX_REG145_RXDFE_CONFIG_SET(val, 0x3);
		val = RXTX_REG145_TX_IDLE_SATA_SET(val, 0x0);
		if (preA3Chip) {
			val = RXTX_REG145_RXES_ENA_SET(val, 0x1);
			val = RXTX_REG145_RXVWES_LATENA_SET(val, 0x1);
		} else {
			val = RXTX_REG145_RXES_ENA_SET(val, 0x0);
			val = RXTX_REG145_RXVWES_LATENA_SET(val, 0x0);
		}
		serdes_wr(ctx, lane, RXTX_REG145, val);

		/*
		 * Set Rx LOS filter clock rate, sample rate, and threshold
		 * windows
		 */
		for (i = 0; i < 4; i++) {
			reg = RXTX_REG148 + i * 2;
			serdes_wr(ctx, lane, reg, 0xFFFF);
		}
	}
}