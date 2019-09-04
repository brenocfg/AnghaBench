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
typedef  scalar_t__ u32 ;
struct mtk_sys_cap {int /*<<< orphan*/  hw_opt; int /*<<< orphan*/  hia_opt; } ;
struct mtk_cryp {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DFE_CFG ; 
 scalar_t__ DSE_CFG ; 
 int MTK_DFE_MAX_CTRL (scalar_t__) ; 
 int MTK_DFE_MIN_CTRL (scalar_t__) ; 
 int MTK_DFSE_MAX_DATA (scalar_t__) ; 
 int MTK_DFSE_MIN_DATA (scalar_t__) ; 
 scalar_t__ MTK_HIA_DATA_WIDTH (int /*<<< orphan*/ ) ; 
 scalar_t__ MTK_HIA_DMA_LENGTH (int /*<<< orphan*/ ) ; 
 int MTK_IN_BUF_MAX_THRESH (scalar_t__) ; 
 int MTK_IN_BUF_MIN_THRESH (scalar_t__) ; 
 scalar_t__ MTK_IN_DBUF_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MTK_IN_TBUF_SIZE (int /*<<< orphan*/ ) ; 
 int MTK_OUT_BUF_MAX_THRESH (scalar_t__) ; 
 int MTK_OUT_BUF_MIN_THRESH (scalar_t__) ; 
 scalar_t__ MTK_OUT_DBUF_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ PE_IN_DBUF_THRESH ; 
 scalar_t__ PE_IN_TBUF_THRESH ; 
 scalar_t__ PE_OUT_BUF_CTRL ; 
 scalar_t__ PE_OUT_DBUF_THRESH ; 
 scalar_t__ PE_OUT_TBUF_THRESH ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_dfe_dse_buf_setup(struct mtk_cryp *cryp,
				  struct mtk_sys_cap *cap)
{
	u32 width = MTK_HIA_DATA_WIDTH(cap->hia_opt) + 2;
	u32 len = MTK_HIA_DMA_LENGTH(cap->hia_opt) - 1;
	u32 ipbuf = min((u32)MTK_IN_DBUF_SIZE(cap->hw_opt) + width, len);
	u32 opbuf = min((u32)MTK_OUT_DBUF_SIZE(cap->hw_opt) + width, len);
	u32 itbuf = min((u32)MTK_IN_TBUF_SIZE(cap->hw_opt) + width, len);

	writel(MTK_DFSE_MIN_DATA(ipbuf - 1) |
	       MTK_DFSE_MAX_DATA(ipbuf) |
	       MTK_DFE_MIN_CTRL(itbuf - 1) |
	       MTK_DFE_MAX_CTRL(itbuf),
	       cryp->base + DFE_CFG);

	writel(MTK_DFSE_MIN_DATA(opbuf - 1) |
	       MTK_DFSE_MAX_DATA(opbuf),
	       cryp->base + DSE_CFG);

	writel(MTK_IN_BUF_MIN_THRESH(ipbuf - 1) |
	       MTK_IN_BUF_MAX_THRESH(ipbuf),
	       cryp->base + PE_IN_DBUF_THRESH);

	writel(MTK_IN_BUF_MIN_THRESH(itbuf - 1) |
	       MTK_IN_BUF_MAX_THRESH(itbuf),
	       cryp->base + PE_IN_TBUF_THRESH);

	writel(MTK_OUT_BUF_MIN_THRESH(opbuf - 1) |
	       MTK_OUT_BUF_MAX_THRESH(opbuf),
	       cryp->base + PE_OUT_DBUF_THRESH);

	writel(0, cryp->base + PE_OUT_TBUF_THRESH);
	writel(0, cryp->base + PE_OUT_BUF_CTRL);
}