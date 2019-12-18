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
typedef  int u32 ;
struct xgene_phy_ctx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXTX_REG12 ; 
 int /*<<< orphan*/  RXTX_REG121 ; 
 int RXTX_REG121_SUMOS_CAL_CODE_RD (int) ; 
 int /*<<< orphan*/  RXTX_REG127 ; 
 int RXTX_REG127_DO_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG127_LATCH_MAN_CAL_ENA_SET (int,int) ; 
 int RXTX_REG127_XO_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXTX_REG128 ; 
 int RXTX_REG128_EO_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG128_SO_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXTX_REG129 ; 
 int RXTX_REG129_DE_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG129_XE_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXTX_REG12_RX_DET_TERM_ENABLE_MASK ; 
 int RXTX_REG12_RX_DET_TERM_ENABLE_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXTX_REG130 ; 
 int RXTX_REG130_EE_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG130_SE_LATCH_MANCAL_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXTX_REG14 ; 
 int RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET (int,int /*<<< orphan*/ ) ; 
 int RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET (int,int) ; 
 int /*<<< orphan*/  RXTX_REG21 ; 
 int RXTX_REG21_DO_LATCH_CALOUT_RD (int) ; 
 int RXTX_REG21_LATCH_CAL_FAIL_ODD_RD (int) ; 
 int RXTX_REG21_XO_LATCH_CALOUT_RD (int) ; 
 int /*<<< orphan*/  RXTX_REG22 ; 
 int RXTX_REG22_EO_LATCH_CALOUT_RD (int) ; 
 int RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD (int) ; 
 int RXTX_REG22_SO_LATCH_CALOUT_RD (int) ; 
 int /*<<< orphan*/  RXTX_REG23 ; 
 int RXTX_REG23_DE_LATCH_CALOUT_RD (int) ; 
 int RXTX_REG23_XE_LATCH_CALOUT_RD (int) ; 
 int /*<<< orphan*/  RXTX_REG24 ; 
 int RXTX_REG24_EE_LATCH_CALOUT_RD (int) ; 
 int RXTX_REG24_SE_LATCH_CALOUT_RD (int) ; 
 int /*<<< orphan*/  RXTX_REG28 ; 
 int /*<<< orphan*/  RXTX_REG31 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  serdes_rd (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  serdes_setbits (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdes_wr (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_phy_force_lat_summer_cal (struct xgene_phy_ctx*,int) ; 
 int /*<<< orphan*/  xgene_phy_get_avg (int,int) ; 
 int /*<<< orphan*/  xgene_phy_reset_rxd (struct xgene_phy_ctx*,int) ; 

__attribute__((used)) static void xgene_phy_gen_avg_val(struct xgene_phy_ctx *ctx, int lane)
{
	int max_loop = 10;
	int avg_loop = 0;
	int lat_do = 0, lat_xo = 0, lat_eo = 0, lat_so = 0;
	int lat_de = 0, lat_xe = 0, lat_ee = 0, lat_se = 0;
	int sum_cal = 0;
	int lat_do_itr, lat_xo_itr, lat_eo_itr, lat_so_itr;
	int lat_de_itr, lat_xe_itr, lat_ee_itr, lat_se_itr;
	int sum_cal_itr;
	int fail_even;
	int fail_odd;
	u32 val;

	dev_dbg(ctx->dev, "Generating avg calibration value for lane %d\n",
		lane);

	/* Enable RX Hi-Z termination */
	serdes_setbits(ctx, lane, RXTX_REG12,
			RXTX_REG12_RX_DET_TERM_ENABLE_MASK);
	/* Turn off DFE */
	serdes_wr(ctx, lane, RXTX_REG28, 0x0000);
	/* DFE Presets to zero */
	serdes_wr(ctx, lane, RXTX_REG31, 0x0000);

	/*
	 * Receiver Offset Calibration:
	 * Calibrate the receiver signal path offset in two steps - summar
	 * and latch calibration.
	 * Runs the "Receiver Offset Calibration multiple times to determine
	 * the average value to use.
	 */
	while (avg_loop < max_loop) {
		/* Start the calibration */
		xgene_phy_force_lat_summer_cal(ctx, lane);

		serdes_rd(ctx, lane, RXTX_REG21, &val);
		lat_do_itr = RXTX_REG21_DO_LATCH_CALOUT_RD(val);
		lat_xo_itr = RXTX_REG21_XO_LATCH_CALOUT_RD(val);
		fail_odd = RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(val);

		serdes_rd(ctx, lane, RXTX_REG22, &val);
		lat_eo_itr = RXTX_REG22_EO_LATCH_CALOUT_RD(val);
		lat_so_itr = RXTX_REG22_SO_LATCH_CALOUT_RD(val);
		fail_even = RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(val);

		serdes_rd(ctx, lane, RXTX_REG23, &val);
		lat_de_itr = RXTX_REG23_DE_LATCH_CALOUT_RD(val);
		lat_xe_itr = RXTX_REG23_XE_LATCH_CALOUT_RD(val);

		serdes_rd(ctx, lane, RXTX_REG24, &val);
		lat_ee_itr = RXTX_REG24_EE_LATCH_CALOUT_RD(val);
		lat_se_itr = RXTX_REG24_SE_LATCH_CALOUT_RD(val);

		serdes_rd(ctx, lane, RXTX_REG121, &val);
		sum_cal_itr = RXTX_REG121_SUMOS_CAL_CODE_RD(val);

		/* Check for failure. If passed, sum them for averaging */
		if ((fail_even == 0 || fail_even == 1) &&
		    (fail_odd == 0 || fail_odd == 1)) {
			lat_do += lat_do_itr;
			lat_xo += lat_xo_itr;
			lat_eo += lat_eo_itr;
			lat_so += lat_so_itr;
			lat_de += lat_de_itr;
			lat_xe += lat_xe_itr;
			lat_ee += lat_ee_itr;
			lat_se += lat_se_itr;
			sum_cal += sum_cal_itr;

			dev_dbg(ctx->dev, "Iteration %d:\n", avg_loop);
			dev_dbg(ctx->dev, "DO 0x%x XO 0x%x EO 0x%x SO 0x%x\n",
				lat_do_itr, lat_xo_itr, lat_eo_itr,
				lat_so_itr);
			dev_dbg(ctx->dev, "DE 0x%x XE 0x%x EE 0x%x SE 0x%x\n",
				lat_de_itr, lat_xe_itr, lat_ee_itr,
				lat_se_itr);
			dev_dbg(ctx->dev, "SUM 0x%x\n", sum_cal_itr);
			++avg_loop;
		} else {
			dev_err(ctx->dev,
				"Receiver calibration failed at %d loop\n",
				avg_loop);
		}
		xgene_phy_reset_rxd(ctx, lane);
	}

	/* Update latch manual calibration with average value */
	serdes_rd(ctx, lane, RXTX_REG127, &val);
	val = RXTX_REG127_DO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_do, max_loop));
	val = RXTX_REG127_XO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_xo, max_loop));
	serdes_wr(ctx, lane, RXTX_REG127, val);

	serdes_rd(ctx, lane, RXTX_REG128, &val);
	val = RXTX_REG128_EO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_eo, max_loop));
	val = RXTX_REG128_SO_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_so, max_loop));
	serdes_wr(ctx, lane, RXTX_REG128, val);

	serdes_rd(ctx, lane, RXTX_REG129, &val);
	val = RXTX_REG129_DE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_de, max_loop));
	val = RXTX_REG129_XE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_xe, max_loop));
	serdes_wr(ctx, lane, RXTX_REG129, val);

	serdes_rd(ctx, lane, RXTX_REG130, &val);
	val = RXTX_REG130_EE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_ee, max_loop));
	val = RXTX_REG130_SE_LATCH_MANCAL_SET(val,
		xgene_phy_get_avg(lat_se, max_loop));
	serdes_wr(ctx, lane, RXTX_REG130, val);

	/* Update SUMMER calibration with average value */
	serdes_rd(ctx, lane, RXTX_REG14, &val);
	val = RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(val,
		xgene_phy_get_avg(sum_cal, max_loop));
	serdes_wr(ctx, lane, RXTX_REG14, val);

	dev_dbg(ctx->dev, "Average Value:\n");
	dev_dbg(ctx->dev, "DO 0x%x XO 0x%x EO 0x%x SO 0x%x\n",
		 xgene_phy_get_avg(lat_do, max_loop),
		 xgene_phy_get_avg(lat_xo, max_loop),
		 xgene_phy_get_avg(lat_eo, max_loop),
		 xgene_phy_get_avg(lat_so, max_loop));
	dev_dbg(ctx->dev, "DE 0x%x XE 0x%x EE 0x%x SE 0x%x\n",
		 xgene_phy_get_avg(lat_de, max_loop),
		 xgene_phy_get_avg(lat_xe, max_loop),
		 xgene_phy_get_avg(lat_ee, max_loop),
		 xgene_phy_get_avg(lat_se, max_loop));
	dev_dbg(ctx->dev, "SUM 0x%x\n",
		xgene_phy_get_avg(sum_cal, max_loop));

	serdes_rd(ctx, lane, RXTX_REG14, &val);
	val = RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(val, 0x1);
	serdes_wr(ctx, lane, RXTX_REG14, val);
	dev_dbg(ctx->dev, "Enable Manual Summer calibration\n");

	serdes_rd(ctx, lane, RXTX_REG127, &val);
	val = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(val, 0x1);
	dev_dbg(ctx->dev, "Enable Manual Latch calibration\n");
	serdes_wr(ctx, lane, RXTX_REG127, val);

	/* Disable RX Hi-Z termination */
	serdes_rd(ctx, lane, RXTX_REG12, &val);
	val = RXTX_REG12_RX_DET_TERM_ENABLE_SET(val, 0);
	serdes_wr(ctx, lane, RXTX_REG12, val);
	/* Turn on DFE */
	serdes_wr(ctx, lane, RXTX_REG28, 0x0007);
	/* Set DFE preset */
	serdes_wr(ctx, lane, RXTX_REG31, 0x7e00);
}