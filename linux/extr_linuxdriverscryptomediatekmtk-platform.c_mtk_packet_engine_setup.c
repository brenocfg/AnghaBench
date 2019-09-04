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
typedef  scalar_t__ u16 ;
struct mtk_sys_cap {void* hia_ver; void* hw_opt; void* hia_opt; } ;
struct mtk_cryp {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AIC_G_ACK ; 
 int EINVAL ; 
 scalar_t__ EIP97_MST_CTRL ; 
 scalar_t__ EIP97_OPTIONS ; 
 scalar_t__ HIA_MST_CTRL ; 
 scalar_t__ HIA_OPTIONS ; 
 scalar_t__ HIA_VERSION ; 
 int MTK_AIC_G_CLR ; 
 int MTK_BURST_SIZE (int) ; 
 int MTK_BURST_SIZE_MSK ; 
 scalar_t__ MTK_HIA_SIGNATURE ; 
 int MTK_PE_FATAL_ERR ; 
 int MTK_PE_FATAL_ERR_EN ; 
 int MTK_PE_INPUT_DMA_ERR ; 
 int MTK_PE_INPUT_DMA_ERR_EN ; 
 int MTK_PE_INT_OUT_EN ; 
 int MTK_PE_OUTPUT_DMA_ERR ; 
 int MTK_PE_OUTPUT_DMA_ERR_EN ; 
 int MTK_PE_PKT_PORC_ERR ; 
 int MTK_PE_PKT_PORC_ERR_EN ; 
 int MTK_PE_PKT_TIMEOUT ; 
 int MTK_PE_PKT_TIMEOUT_EN ; 
 int MTK_PE_PROC_HELD ; 
 int MTK_PE_TK_LOC_AVL ; 
 int MTK_PE_TK_TIMEOUT_EN ; 
 int MTK_RING_MAX ; 
 scalar_t__ PE_INTERRUPT_CTRL_STAT ; 
 scalar_t__ PE_TOKEN_CTRL_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtk_cmd_desc_ring_setup (struct mtk_cryp*,int,struct mtk_sys_cap*) ; 
 int /*<<< orphan*/  mtk_desc_ring_link (struct mtk_cryp*,int) ; 
 int /*<<< orphan*/  mtk_dfe_dse_buf_setup (struct mtk_cryp*,struct mtk_sys_cap*) ; 
 int mtk_dfe_dse_reset (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_res_desc_ring_setup (struct mtk_cryp*,int,struct mtk_sys_cap*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_packet_engine_setup(struct mtk_cryp *cryp)
{
	struct mtk_sys_cap cap;
	int i, err;
	u32 val;

	cap.hia_ver = readl(cryp->base + HIA_VERSION);
	cap.hia_opt = readl(cryp->base + HIA_OPTIONS);
	cap.hw_opt = readl(cryp->base + EIP97_OPTIONS);

	if (!(((u16)cap.hia_ver) == MTK_HIA_SIGNATURE))
		return -EINVAL;

	/* Configure endianness conversion method for master (DMA) interface */
	writel(0, cryp->base + EIP97_MST_CTRL);

	/* Set HIA burst size */
	val = readl(cryp->base + HIA_MST_CTRL);
	val &= ~MTK_BURST_SIZE_MSK;
	val |= MTK_BURST_SIZE(5);
	writel(val, cryp->base + HIA_MST_CTRL);

	err = mtk_dfe_dse_reset(cryp);
	if (err) {
		dev_err(cryp->dev, "Failed to reset DFE and DSE.\n");
		return err;
	}

	mtk_dfe_dse_buf_setup(cryp, &cap);

	/* Enable the 4 rings for the packet engines. */
	mtk_desc_ring_link(cryp, 0xf);

	for (i = 0; i < MTK_RING_MAX; i++) {
		mtk_cmd_desc_ring_setup(cryp, i, &cap);
		mtk_res_desc_ring_setup(cryp, i, &cap);
	}

	writel(MTK_PE_TK_LOC_AVL | MTK_PE_PROC_HELD | MTK_PE_TK_TIMEOUT_EN,
	       cryp->base + PE_TOKEN_CTRL_STAT);

	/* Clear all pending interrupts */
	writel(MTK_AIC_G_CLR, cryp->base + AIC_G_ACK);
	writel(MTK_PE_INPUT_DMA_ERR | MTK_PE_OUTPUT_DMA_ERR |
	       MTK_PE_PKT_PORC_ERR | MTK_PE_PKT_TIMEOUT |
	       MTK_PE_FATAL_ERR | MTK_PE_INPUT_DMA_ERR_EN |
	       MTK_PE_OUTPUT_DMA_ERR_EN | MTK_PE_PKT_PORC_ERR_EN |
	       MTK_PE_PKT_TIMEOUT_EN | MTK_PE_FATAL_ERR_EN |
	       MTK_PE_INT_OUT_EN,
	       cryp->base + PE_INTERRUPT_CTRL_STAT);

	return 0;
}