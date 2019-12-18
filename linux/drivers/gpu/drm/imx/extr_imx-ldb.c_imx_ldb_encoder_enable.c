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
struct imx_ldb_channel {size_t chno; int /*<<< orphan*/  panel; int /*<<< orphan*/  child; struct imx_ldb* ldb; } ;
struct imx_ldb {int ldb_ctrl; int /*<<< orphan*/  regmap; struct bus_mux* lvds_mux; struct imx_ldb_channel* channel; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * clk_sel; } ;
struct drm_encoder {int dummy; } ;
struct bus_mux {int shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUXC_GPR2 ; 
 int LDB_CH0_MODE_EN_MASK ; 
 int LDB_CH0_MODE_EN_TO_DI0 ; 
 int LDB_CH0_MODE_EN_TO_DI1 ; 
 int LDB_CH1_MODE_EN_MASK ; 
 int LDB_CH1_MODE_EN_TO_DI0 ; 
 int LDB_CH1_MODE_EN_TO_DI1 ; 
 int LDB_SPLIT_MODE_EN ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_of_encoder_active_port_id (int /*<<< orphan*/ ,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ ) ; 
 struct imx_ldb_channel* enc_to_imx_ldb_ch (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imx_ldb_encoder_enable(struct drm_encoder *encoder)
{
	struct imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	struct imx_ldb *ldb = imx_ldb_ch->ldb;
	int dual = ldb->ldb_ctrl & LDB_SPLIT_MODE_EN;
	int mux = drm_of_encoder_active_port_id(imx_ldb_ch->child, encoder);

	drm_panel_prepare(imx_ldb_ch->panel);

	if (dual) {
		clk_set_parent(ldb->clk_sel[mux], ldb->clk[0]);
		clk_set_parent(ldb->clk_sel[mux], ldb->clk[1]);

		clk_prepare_enable(ldb->clk[0]);
		clk_prepare_enable(ldb->clk[1]);
	} else {
		clk_set_parent(ldb->clk_sel[mux], ldb->clk[imx_ldb_ch->chno]);
	}

	if (imx_ldb_ch == &ldb->channel[0] || dual) {
		ldb->ldb_ctrl &= ~LDB_CH0_MODE_EN_MASK;
		if (mux == 0 || ldb->lvds_mux)
			ldb->ldb_ctrl |= LDB_CH0_MODE_EN_TO_DI0;
		else if (mux == 1)
			ldb->ldb_ctrl |= LDB_CH0_MODE_EN_TO_DI1;
	}
	if (imx_ldb_ch == &ldb->channel[1] || dual) {
		ldb->ldb_ctrl &= ~LDB_CH1_MODE_EN_MASK;
		if (mux == 1 || ldb->lvds_mux)
			ldb->ldb_ctrl |= LDB_CH1_MODE_EN_TO_DI1;
		else if (mux == 0)
			ldb->ldb_ctrl |= LDB_CH1_MODE_EN_TO_DI0;
	}

	if (ldb->lvds_mux) {
		const struct bus_mux *lvds_mux = NULL;

		if (imx_ldb_ch == &ldb->channel[0])
			lvds_mux = &ldb->lvds_mux[0];
		else if (imx_ldb_ch == &ldb->channel[1])
			lvds_mux = &ldb->lvds_mux[1];

		regmap_update_bits(ldb->regmap, lvds_mux->reg, lvds_mux->mask,
				   mux << lvds_mux->shift);
	}

	regmap_write(ldb->regmap, IOMUXC_GPR2, ldb->ldb_ctrl);

	drm_panel_enable(imx_ldb_ch->panel);
}