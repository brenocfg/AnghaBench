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
struct xgene_edac_dev_ctx {int /*<<< orphan*/  edac; scalar_t__ dev_csr; } ;
struct edac_device_ctl_info {scalar_t__ op_state; struct xgene_edac_dev_ctx* pvt_info; } ;

/* Variables and functions */
 int L3C_CERREN ; 
 int /*<<< orphan*/  L3C_CORR_ERR_MASK ; 
 scalar_t__ L3C_ECR ; 
 int L3C_ECR_CINTREN ; 
 int L3C_ECR_UCINTREN ; 
 int L3C_UCERREN ; 
 int /*<<< orphan*/  L3C_UNCORR_ERR_MASK ; 
 scalar_t__ OP_RUNNING_INTERRUPT ; 
 int /*<<< orphan*/  PCPHPERRINTMSK ; 
 int /*<<< orphan*/  PCPLPERRINTMSK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  xgene_edac_pcp_clrbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_edac_pcp_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_edac_l3_hw_init(struct edac_device_ctl_info *edac_dev,
				  bool enable)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 val;

	val = readl(ctx->dev_csr + L3C_ECR);
	val |= L3C_UCERREN | L3C_CERREN;
	/* On disable, we just disable interrupt but keep error enabled */
	if (edac_dev->op_state == OP_RUNNING_INTERRUPT) {
		if (enable)
			val |= L3C_ECR_UCINTREN | L3C_ECR_CINTREN;
		else
			val &= ~(L3C_ECR_UCINTREN | L3C_ECR_CINTREN);
	}
	writel(val, ctx->dev_csr + L3C_ECR);

	if (edac_dev->op_state == OP_RUNNING_INTERRUPT) {
		/* Enable/disable L3 error top level interrupt */
		if (enable) {
			xgene_edac_pcp_clrbits(ctx->edac, PCPHPERRINTMSK,
					       L3C_UNCORR_ERR_MASK);
			xgene_edac_pcp_clrbits(ctx->edac, PCPLPERRINTMSK,
					       L3C_CORR_ERR_MASK);
		} else {
			xgene_edac_pcp_setbits(ctx->edac, PCPHPERRINTMSK,
					       L3C_UNCORR_ERR_MASK);
			xgene_edac_pcp_setbits(ctx->edac, PCPLPERRINTMSK,
					       L3C_CORR_ERR_MASK);
		}
	}
}