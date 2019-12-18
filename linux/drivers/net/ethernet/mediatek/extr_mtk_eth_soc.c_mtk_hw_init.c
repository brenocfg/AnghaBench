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
struct mtk_eth {int /*<<< orphan*/  dev; scalar_t__ pctl; TYPE_1__* soc; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_BIAS_CTRL ; 
 int /*<<< orphan*/  GPIO_DRV_SEL10 ; 
 int /*<<< orphan*/  GPIO_OD33_CTRL8 ; 
 int MAC_MCR_FORCE_LINK_DOWN ; 
 int /*<<< orphan*/  MTK_CDMP_EG_CTRL ; 
 int /*<<< orphan*/  MTK_CDMQ_IG_CTRL ; 
 int MTK_CDMQ_STAG_EN ; 
 int /*<<< orphan*/  MTK_FE_INT_GRP ; 
 int /*<<< orphan*/  MTK_GDMA_FWD_CFG (int) ; 
 int MTK_GDMA_ICS_EN ; 
 int MTK_GDMA_TCS_EN ; 
 int MTK_GDMA_UCS_EN ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_HW_INIT ; 
 int MTK_MAC_COUNT ; 
 int /*<<< orphan*/  MTK_MAC_MCR (int) ; 
 int /*<<< orphan*/  MTK_PDMA_DELAY_INT ; 
 int MTK_PDMA_DELAY_RX_DELAY ; 
 int /*<<< orphan*/  MTK_PDMA_INT_GRP1 ; 
 int /*<<< orphan*/  MTK_PDMA_INT_GRP2 ; 
 int /*<<< orphan*/  MTK_QDMA_DELAY_INT ; 
 int /*<<< orphan*/  MTK_QDMA_INT_GRP1 ; 
 int /*<<< orphan*/  MTK_QDMA_INT_GRP2 ; 
 int /*<<< orphan*/  MTK_RST_GL ; 
 int MTK_RX_DONE_INT ; 
 int /*<<< orphan*/  MTK_SOC_MT7628 ; 
 int MTK_TX_DONE_INT ; 
 int /*<<< orphan*/  RSTCTRL_FE ; 
 int /*<<< orphan*/  RSTCTRL_PPE ; 
 int RST_GL_PSE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int device_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethsys_reset (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int mtk_clk_enable (struct mtk_eth*) ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rx_irq_disable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_tx_irq_disable (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_hw_init(struct mtk_eth *eth)
{
	int i, val, ret;

	if (test_and_set_bit(MTK_HW_INIT, &eth->state))
		return 0;

	pm_runtime_enable(eth->dev);
	pm_runtime_get_sync(eth->dev);

	ret = mtk_clk_enable(eth);
	if (ret)
		goto err_disable_pm;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		ret = device_reset(eth->dev);
		if (ret) {
			dev_err(eth->dev, "MAC reset failed!\n");
			goto err_disable_pm;
		}

		/* enable interrupt delay for RX */
		mtk_w32(eth, MTK_PDMA_DELAY_RX_DELAY, MTK_PDMA_DELAY_INT);

		/* disable delay and normal interrupt */
		mtk_tx_irq_disable(eth, ~0);
		mtk_rx_irq_disable(eth, ~0);

		return 0;
	}

	/* Non-MT7628 handling... */
	ethsys_reset(eth, RSTCTRL_FE);
	ethsys_reset(eth, RSTCTRL_PPE);

	if (eth->pctl) {
		/* Set GE2 driving and slew rate */
		regmap_write(eth->pctl, GPIO_DRV_SEL10, 0xa00);

		/* set GE2 TDSEL */
		regmap_write(eth->pctl, GPIO_OD33_CTRL8, 0x5);

		/* set GE2 TUNE */
		regmap_write(eth->pctl, GPIO_BIAS_CTRL, 0x0);
	}

	/* Set linkdown as the default for each GMAC. Its own MCR would be set
	 * up with the more appropriate value when mtk_mac_config call is being
	 * invoked.
	 */
	for (i = 0; i < MTK_MAC_COUNT; i++)
		mtk_w32(eth, MAC_MCR_FORCE_LINK_DOWN, MTK_MAC_MCR(i));

	/* Indicates CDM to parse the MTK special tag from CPU
	 * which also is working out for untag packets.
	 */
	val = mtk_r32(eth, MTK_CDMQ_IG_CTRL);
	mtk_w32(eth, val | MTK_CDMQ_STAG_EN, MTK_CDMQ_IG_CTRL);

	/* Enable RX VLan Offloading */
	mtk_w32(eth, 1, MTK_CDMP_EG_CTRL);

	/* enable interrupt delay for RX */
	mtk_w32(eth, MTK_PDMA_DELAY_RX_DELAY, MTK_PDMA_DELAY_INT);

	/* disable delay and normal interrupt */
	mtk_w32(eth, 0, MTK_QDMA_DELAY_INT);
	mtk_tx_irq_disable(eth, ~0);
	mtk_rx_irq_disable(eth, ~0);
	mtk_w32(eth, RST_GL_PSE, MTK_RST_GL);
	mtk_w32(eth, 0, MTK_RST_GL);

	/* FE int grouping */
	mtk_w32(eth, MTK_TX_DONE_INT, MTK_PDMA_INT_GRP1);
	mtk_w32(eth, MTK_RX_DONE_INT, MTK_PDMA_INT_GRP2);
	mtk_w32(eth, MTK_TX_DONE_INT, MTK_QDMA_INT_GRP1);
	mtk_w32(eth, MTK_RX_DONE_INT, MTK_QDMA_INT_GRP2);
	mtk_w32(eth, 0x21021000, MTK_FE_INT_GRP);

	for (i = 0; i < MTK_MAC_COUNT; i++) {
		u32 val = mtk_r32(eth, MTK_GDMA_FWD_CFG(i));

		/* setup the forward port to send frame to PDMA */
		val &= ~0xffff;

		/* Enable RX checksum */
		val |= MTK_GDMA_ICS_EN | MTK_GDMA_TCS_EN | MTK_GDMA_UCS_EN;

		/* setup the mac dma */
		mtk_w32(eth, val, MTK_GDMA_FWD_CFG(i));
	}

	return 0;

err_disable_pm:
	pm_runtime_put_sync(eth->dev);
	pm_runtime_disable(eth->dev);

	return ret;
}