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
struct imx_ldb_channel {int /*<<< orphan*/  panel; struct imx_ldb* ldb; } ;
struct imx_ldb {int ldb_ctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/ * clk_parent; int /*<<< orphan*/ * clk_sel; struct imx_ldb_channel* channel; int /*<<< orphan*/  regmap; struct bus_mux* lvds_mux; int /*<<< orphan*/ * clk; } ;
struct drm_encoder {int dummy; } ;
struct bus_mux {int mask; int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUXC_GPR2 ; 
 int LDB_CH0_MODE_EN_MASK ; 
 int LDB_CH1_MODE_EN_MASK ; 
 int LDB_SPLIT_MODE_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 struct imx_ldb_channel* enc_to_imx_ldb_ch (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imx_ldb_encoder_disable(struct drm_encoder *encoder)
{
	struct imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	struct imx_ldb *ldb = imx_ldb_ch->ldb;
	int mux, ret;

	drm_panel_disable(imx_ldb_ch->panel);

	if (imx_ldb_ch == &ldb->channel[0])
		ldb->ldb_ctrl &= ~LDB_CH0_MODE_EN_MASK;
	else if (imx_ldb_ch == &ldb->channel[1])
		ldb->ldb_ctrl &= ~LDB_CH1_MODE_EN_MASK;

	regmap_write(ldb->regmap, IOMUXC_GPR2, ldb->ldb_ctrl);

	if (ldb->ldb_ctrl & LDB_SPLIT_MODE_EN) {
		clk_disable_unprepare(ldb->clk[0]);
		clk_disable_unprepare(ldb->clk[1]);
	}

	if (ldb->lvds_mux) {
		const struct bus_mux *lvds_mux = NULL;

		if (imx_ldb_ch == &ldb->channel[0])
			lvds_mux = &ldb->lvds_mux[0];
		else if (imx_ldb_ch == &ldb->channel[1])
			lvds_mux = &ldb->lvds_mux[1];

		regmap_read(ldb->regmap, lvds_mux->reg, &mux);
		mux &= lvds_mux->mask;
		mux >>= lvds_mux->shift;
	} else {
		mux = (imx_ldb_ch == &ldb->channel[0]) ? 0 : 1;
	}

	/* set display clock mux back to original input clock */
	ret = clk_set_parent(ldb->clk_sel[mux], ldb->clk_parent[mux]);
	if (ret)
		dev_err(ldb->dev,
			"unable to set di%d parent clock to original parent\n",
			mux);

	drm_panel_unprepare(imx_ldb_ch->panel);
}