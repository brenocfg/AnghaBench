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
typedef  int u64 ;
struct mtk_mipi_tx {int data_rate; TYPE_1__* driver_data; scalar_t__ regs; int /*<<< orphan*/  dev; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int mppll_preserve; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIPITX_DSI_BG_CON ; 
 int /*<<< orphan*/  MIPITX_DSI_CON ; 
 int /*<<< orphan*/  MIPITX_DSI_PLL_CON0 ; 
 int /*<<< orphan*/  MIPITX_DSI_PLL_CON1 ; 
 scalar_t__ MIPITX_DSI_PLL_CON2 ; 
 int /*<<< orphan*/  MIPITX_DSI_PLL_PWR ; 
 int /*<<< orphan*/  MIPITX_DSI_PLL_TOP ; 
 int /*<<< orphan*/  MIPITX_DSI_TOP_CON ; 
 int RG_DSI_BG_CKEN ; 
 int RG_DSI_BG_CORE_EN ; 
 int RG_DSI_CKG_LDOOUT_EN ; 
 int RG_DSI_LDOCORE_EN ; 
 int RG_DSI_LNT_HS_BIAS_EN ; 
 int RG_DSI_LNT_IMP_CAL_CODE ; 
 int RG_DSI_MPPLL_PLL_EN ; 
 int RG_DSI_MPPLL_PREDIV ; 
 int RG_DSI_MPPLL_PRESERVE ; 
 int RG_DSI_MPPLL_SDM_FRA_EN ; 
 int RG_DSI_MPPLL_SDM_ISO_EN ; 
 int RG_DSI_MPPLL_SDM_PWR_ON ; 
 int RG_DSI_MPPLL_SDM_SSC_EN ; 
 int RG_DSI_MPPLL_TXDIV0 ; 
 int RG_DSI_MPPLL_TXDIV1 ; 
 int RG_DSI_VOUT_MSK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  mtk_mipi_tx_clear_bits (struct mtk_mipi_tx*,int /*<<< orphan*/ ,int) ; 
 struct mtk_mipi_tx* mtk_mipi_tx_from_clk_hw (struct clk_hw*) ; 
 int /*<<< orphan*/  mtk_mipi_tx_set_bits (struct mtk_mipi_tx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_mipi_tx_update_bits (struct mtk_mipi_tx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_mipi_tx_pll_prepare(struct clk_hw *hw)
{
	struct mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);
	u8 txdiv, txdiv0, txdiv1;
	u64 pcw;

	dev_dbg(mipi_tx->dev, "prepare: %u Hz\n", mipi_tx->data_rate);

	if (mipi_tx->data_rate >= 500000000) {
		txdiv = 1;
		txdiv0 = 0;
		txdiv1 = 0;
	} else if (mipi_tx->data_rate >= 250000000) {
		txdiv = 2;
		txdiv0 = 1;
		txdiv1 = 0;
	} else if (mipi_tx->data_rate >= 125000000) {
		txdiv = 4;
		txdiv0 = 2;
		txdiv1 = 0;
	} else if (mipi_tx->data_rate > 62000000) {
		txdiv = 8;
		txdiv0 = 2;
		txdiv1 = 1;
	} else if (mipi_tx->data_rate >= 50000000) {
		txdiv = 16;
		txdiv0 = 2;
		txdiv1 = 2;
	} else {
		return -EINVAL;
	}

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_BG_CON,
				RG_DSI_VOUT_MSK |
				RG_DSI_BG_CKEN | RG_DSI_BG_CORE_EN,
				(4 << 20) | (4 << 17) | (4 << 14) |
				(4 << 11) | (4 << 8) | (4 << 5) |
				RG_DSI_BG_CKEN | RG_DSI_BG_CORE_EN);

	usleep_range(30, 100);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_TOP_CON,
				RG_DSI_LNT_IMP_CAL_CODE | RG_DSI_LNT_HS_BIAS_EN,
				(8 << 4) | RG_DSI_LNT_HS_BIAS_EN);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_CON,
			     RG_DSI_CKG_LDOOUT_EN | RG_DSI_LDOCORE_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_PWR,
				RG_DSI_MPPLL_SDM_PWR_ON |
				RG_DSI_MPPLL_SDM_ISO_EN,
				RG_DSI_MPPLL_SDM_PWR_ON);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_PLL_CON0,
			       RG_DSI_MPPLL_PLL_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_CON0,
				RG_DSI_MPPLL_TXDIV0 | RG_DSI_MPPLL_TXDIV1 |
				RG_DSI_MPPLL_PREDIV,
				(txdiv0 << 3) | (txdiv1 << 5));

	/*
	 * PLL PCW config
	 * PCW bit 24~30 = integer part of pcw
	 * PCW bit 0~23 = fractional part of pcw
	 * pcw = data_Rate*4*txdiv/(Ref_clk*2);
	 * Post DIV =4, so need data_Rate*4
	 * Ref_clk is 26MHz
	 */
	pcw = div_u64(((u64)mipi_tx->data_rate * 2 * txdiv) << 24,
		      26000000);
	writel(pcw, mipi_tx->regs + MIPITX_DSI_PLL_CON2);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_PLL_CON1,
			     RG_DSI_MPPLL_SDM_FRA_EN);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_PLL_CON0, RG_DSI_MPPLL_PLL_EN);

	usleep_range(20, 100);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_PLL_CON1,
			       RG_DSI_MPPLL_SDM_SSC_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_TOP,
				RG_DSI_MPPLL_PRESERVE,
				mipi_tx->driver_data->mppll_preserve);

	return 0;
}