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
struct xgene_edac_dev_ctx {scalar_t__ dev_csr; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  dev; struct xgene_edac_dev_ctx* pvt_info; } ;

/* Variables and functions */
 int DED_ERR_MASK ; 
 int /*<<< orphan*/  ERRADDR_RD (int) ; 
 scalar_t__ GLBL_DED_ERRH ; 
 scalar_t__ GLBL_DED_ERRL ; 
 scalar_t__ GLBL_ERR_STS ; 
 scalar_t__ GLBL_MDED_ERRH ; 
 scalar_t__ GLBL_MDED_ERRL ; 
 scalar_t__ GLBL_MSEC_ERRH ; 
 scalar_t__ GLBL_MSEC_ERRL ; 
 scalar_t__ GLBL_SEC_ERRH ; 
 scalar_t__ GLBL_SEC_ERRL ; 
 int MDED_ERR_MASK ; 
 int MSEC_ERR_MASK ; 
 int M_RD_ACCESS_ERR_MASK ; 
 int M_WR_ACCESS_ERR_MASK ; 
 int RD_ACCESS_ERR_MASK ; 
 int REQTYPE_MASK ; 
 int SEC_ERR_MASK ; 
 int WR_ACCESS_ERR_MASK ; 
 scalar_t__ XGICTRANSERRINTSTS ; 
 scalar_t__ XGICTRANSERRREQINFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void xgene_edac_iob_gic_report(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 err_addr_lo;
	u32 err_addr_hi;
	u32 reg;
	u32 info;

	/* GIC transaction error interrupt */
	reg = readl(ctx->dev_csr + XGICTRANSERRINTSTS);
	if (!reg)
		goto chk_iob_err;
	dev_err(edac_dev->dev, "XGIC transaction error\n");
	if (reg & RD_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "XGIC read size error\n");
	if (reg & M_RD_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "Multiple XGIC read size error\n");
	if (reg & WR_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "XGIC write size error\n");
	if (reg & M_WR_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "Multiple XGIC write size error\n");
	info = readl(ctx->dev_csr + XGICTRANSERRREQINFO);
	dev_err(edac_dev->dev, "XGIC %s access @ 0x%08X (0x%08X)\n",
		info & REQTYPE_MASK ? "read" : "write", ERRADDR_RD(info),
		info);
	writel(reg, ctx->dev_csr + XGICTRANSERRINTSTS);

chk_iob_err:
	/* IOB memory error */
	reg = readl(ctx->dev_csr + GLBL_ERR_STS);
	if (!reg)
		return;
	if (reg & SEC_ERR_MASK) {
		err_addr_lo = readl(ctx->dev_csr + GLBL_SEC_ERRL);
		err_addr_hi = readl(ctx->dev_csr + GLBL_SEC_ERRH);
		dev_err(edac_dev->dev,
			"IOB single-bit correctable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		writel(err_addr_lo, ctx->dev_csr + GLBL_SEC_ERRL);
		writel(err_addr_hi, ctx->dev_csr + GLBL_SEC_ERRH);
	}
	if (reg & MSEC_ERR_MASK) {
		err_addr_lo = readl(ctx->dev_csr + GLBL_MSEC_ERRL);
		err_addr_hi = readl(ctx->dev_csr + GLBL_MSEC_ERRH);
		dev_err(edac_dev->dev,
			"IOB multiple single-bit correctable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		writel(err_addr_lo, ctx->dev_csr + GLBL_MSEC_ERRL);
		writel(err_addr_hi, ctx->dev_csr + GLBL_MSEC_ERRH);
	}
	if (reg & (SEC_ERR_MASK | MSEC_ERR_MASK))
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);

	if (reg & DED_ERR_MASK) {
		err_addr_lo = readl(ctx->dev_csr + GLBL_DED_ERRL);
		err_addr_hi = readl(ctx->dev_csr + GLBL_DED_ERRH);
		dev_err(edac_dev->dev,
			"IOB double-bit uncorrectable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		writel(err_addr_lo, ctx->dev_csr + GLBL_DED_ERRL);
		writel(err_addr_hi, ctx->dev_csr + GLBL_DED_ERRH);
	}
	if (reg & MDED_ERR_MASK) {
		err_addr_lo = readl(ctx->dev_csr + GLBL_MDED_ERRL);
		err_addr_hi = readl(ctx->dev_csr + GLBL_MDED_ERRH);
		dev_err(edac_dev->dev,
			"Multiple IOB double-bit uncorrectable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		writel(err_addr_lo, ctx->dev_csr + GLBL_MDED_ERRL);
		writel(err_addr_hi, ctx->dev_csr + GLBL_MDED_ERRH);
	}
	if (reg & (DED_ERR_MASK | MDED_ERR_MASK))
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
}