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
typedef  int /*<<< orphan*/  u32 ;
struct tc358764 {int /*<<< orphan*/  dev; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_LANEENABLE ; 
 int DSI_RX_START ; 
 int /*<<< orphan*/  DSI_STARTDSI ; 
 int LANEENABLE_CLEN ; 
 int LANEENABLE_L0EN ; 
 int LANEENABLE_L1EN ; 
 int LANEENABLE_L2EN ; 
 int LANEENABLE_L3EN ; 
 int LPX_PERIOD ; 
 int /*<<< orphan*/  LVI_B0 ; 
 int /*<<< orphan*/  LVI_B1 ; 
 int /*<<< orphan*/  LVI_B2 ; 
 int /*<<< orphan*/  LVI_B3 ; 
 int /*<<< orphan*/  LVI_B4 ; 
 int /*<<< orphan*/  LVI_B5 ; 
 int /*<<< orphan*/  LVI_B6 ; 
 int /*<<< orphan*/  LVI_B7 ; 
 int /*<<< orphan*/  LVI_DE ; 
 int /*<<< orphan*/  LVI_G0 ; 
 int /*<<< orphan*/  LVI_G1 ; 
 int /*<<< orphan*/  LVI_G2 ; 
 int /*<<< orphan*/  LVI_G3 ; 
 int /*<<< orphan*/  LVI_G4 ; 
 int /*<<< orphan*/  LVI_G5 ; 
 int /*<<< orphan*/  LVI_G6 ; 
 int /*<<< orphan*/  LVI_G7 ; 
 int /*<<< orphan*/  LVI_HS ; 
 int /*<<< orphan*/  LVI_L0 ; 
 int /*<<< orphan*/  LVI_R0 ; 
 int /*<<< orphan*/  LVI_R1 ; 
 int /*<<< orphan*/  LVI_R2 ; 
 int /*<<< orphan*/  LVI_R3 ; 
 int /*<<< orphan*/  LVI_R4 ; 
 int /*<<< orphan*/  LVI_R5 ; 
 int /*<<< orphan*/  LVI_R6 ; 
 int /*<<< orphan*/  LVI_R7 ; 
 int /*<<< orphan*/  LVI_VS ; 
 int /*<<< orphan*/  LV_CFG ; 
 int LV_CFG_CLKPOL1 ; 
 int LV_CFG_CLKPOL2 ; 
 int LV_CFG_LVEN ; 
 int LV_MX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LV_MX0003 ; 
 int /*<<< orphan*/  LV_MX0407 ; 
 int /*<<< orphan*/  LV_MX0811 ; 
 int /*<<< orphan*/  LV_MX1215 ; 
 int /*<<< orphan*/  LV_MX1619 ; 
 int /*<<< orphan*/  LV_MX2023 ; 
 int /*<<< orphan*/  LV_MX2427 ; 
 int /*<<< orphan*/  LV_PHY0 ; 
 int LV_PHY0_IS (int) ; 
 int LV_PHY0_ND (int) ; 
 int LV_PHY0_PRBS_ON (int) ; 
 int LV_PHY0_RST (int) ; 
 int /*<<< orphan*/  PPI_D0S_CLRSIPOCOUNT ; 
 int /*<<< orphan*/  PPI_D1S_CLRSIPOCOUNT ; 
 int /*<<< orphan*/  PPI_D2S_CLRSIPOCOUNT ; 
 int /*<<< orphan*/  PPI_D3S_CLRSIPOCOUNT ; 
 int /*<<< orphan*/  PPI_LANEENABLE ; 
 int /*<<< orphan*/  PPI_LPTXTIMECNT ; 
 int /*<<< orphan*/  PPI_STARTPPI ; 
 int PPI_START_FUNCTION ; 
 int /*<<< orphan*/  PPI_TX_RX_TA ; 
 int /*<<< orphan*/  SYS_ID ; 
 int /*<<< orphan*/  SYS_RST ; 
 int SYS_RST_LCD ; 
 int TTA_GET ; 
 int TTA_SURE ; 
 int /*<<< orphan*/  VP_CTRL ; 
 int VP_CTRL_EVTMODE (int) ; 
 int VP_CTRL_HSPOL ; 
 int VP_CTRL_RGB888 (int) ; 
 int VP_CTRL_VSDELAY (int) ; 
 int VP_CTRL_VSPOL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int tc358764_clear_error (struct tc358764*) ; 
 int /*<<< orphan*/  tc358764_read (struct tc358764*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc358764_write (struct tc358764*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc358764_init(struct tc358764 *ctx)
{
	u32 v = 0;

	tc358764_read(ctx, SYS_ID, &v);
	if (ctx->error)
		return tc358764_clear_error(ctx);
	dev_info(ctx->dev, "ID: %#x\n", v);

	/* configure PPI counters */
	tc358764_write(ctx, PPI_TX_RX_TA, TTA_GET | TTA_SURE);
	tc358764_write(ctx, PPI_LPTXTIMECNT, LPX_PERIOD);
	tc358764_write(ctx, PPI_D0S_CLRSIPOCOUNT, 5);
	tc358764_write(ctx, PPI_D1S_CLRSIPOCOUNT, 5);
	tc358764_write(ctx, PPI_D2S_CLRSIPOCOUNT, 5);
	tc358764_write(ctx, PPI_D3S_CLRSIPOCOUNT, 5);

	/* enable four data lanes and clock lane */
	tc358764_write(ctx, PPI_LANEENABLE, LANEENABLE_L3EN | LANEENABLE_L2EN |
		       LANEENABLE_L1EN | LANEENABLE_L0EN | LANEENABLE_CLEN);
	tc358764_write(ctx, DSI_LANEENABLE, LANEENABLE_L3EN | LANEENABLE_L2EN |
		       LANEENABLE_L1EN | LANEENABLE_L0EN | LANEENABLE_CLEN);

	/* start */
	tc358764_write(ctx, PPI_STARTPPI, PPI_START_FUNCTION);
	tc358764_write(ctx, DSI_STARTDSI, DSI_RX_START);

	/* configure video path */
	tc358764_write(ctx, VP_CTRL, VP_CTRL_VSDELAY(15) | VP_CTRL_RGB888(1) |
		       VP_CTRL_EVTMODE(1) | VP_CTRL_HSPOL | VP_CTRL_VSPOL);

	/* reset PHY */
	tc358764_write(ctx, LV_PHY0, LV_PHY0_RST(1) |
		       LV_PHY0_PRBS_ON(4) | LV_PHY0_IS(2) | LV_PHY0_ND(6));
	tc358764_write(ctx, LV_PHY0, LV_PHY0_PRBS_ON(4) | LV_PHY0_IS(2) |
		       LV_PHY0_ND(6));

	/* reset bridge */
	tc358764_write(ctx, SYS_RST, SYS_RST_LCD);

	/* set bit order */
	tc358764_write(ctx, LV_MX0003, LV_MX(LVI_R0, LVI_R1, LVI_R2, LVI_R3));
	tc358764_write(ctx, LV_MX0407, LV_MX(LVI_R4, LVI_R7, LVI_R5, LVI_G0));
	tc358764_write(ctx, LV_MX0811, LV_MX(LVI_G1, LVI_G2, LVI_G6, LVI_G7));
	tc358764_write(ctx, LV_MX1215, LV_MX(LVI_G3, LVI_G4, LVI_G5, LVI_B0));
	tc358764_write(ctx, LV_MX1619, LV_MX(LVI_B6, LVI_B7, LVI_B1, LVI_B2));
	tc358764_write(ctx, LV_MX2023, LV_MX(LVI_B3, LVI_B4, LVI_B5, LVI_L0));
	tc358764_write(ctx, LV_MX2427, LV_MX(LVI_HS, LVI_VS, LVI_DE, LVI_R6));
	tc358764_write(ctx, LV_CFG, LV_CFG_CLKPOL2 | LV_CFG_CLKPOL1 |
		       LV_CFG_LVEN);

	return tc358764_clear_error(ctx);
}