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
struct xgene_edac_dev_ctx {int version; int /*<<< orphan*/  edac; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  dev; struct xgene_edac_dev_ctx* pvt_info; } ;

/* Variables and functions */
 int CSW_SWITCH_TRACE_ERR_MASK ; 
 int IOB_BA_ERR_MASK ; 
 int IOB_PA_ERR_MASK ; 
 int IOB_RB_ERR_MASK ; 
 int IOB_XGIC_ERR_MASK ; 
 int /*<<< orphan*/  MEMERRINTSTS ; 
 int /*<<< orphan*/  PCPHPERRINTSTS ; 
 int /*<<< orphan*/  PCPLPERRINTSTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** soc_mem_err_v1 ; 
 int /*<<< orphan*/  xgene_edac_iob_gic_report (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  xgene_edac_pa_report (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  xgene_edac_pcp_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xgene_edac_rb_report (struct edac_device_ctl_info*) ; 

__attribute__((used)) static void xgene_edac_soc_check(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	const char * const *soc_mem_err = NULL;
	u32 pcp_hp_stat;
	u32 pcp_lp_stat;
	u32 reg;
	int i;

	xgene_edac_pcp_rd(ctx->edac, PCPHPERRINTSTS, &pcp_hp_stat);
	xgene_edac_pcp_rd(ctx->edac, PCPLPERRINTSTS, &pcp_lp_stat);
	xgene_edac_pcp_rd(ctx->edac, MEMERRINTSTS, &reg);
	if (!((pcp_hp_stat & (IOB_PA_ERR_MASK | IOB_BA_ERR_MASK |
			      IOB_XGIC_ERR_MASK | IOB_RB_ERR_MASK)) ||
	      (pcp_lp_stat & CSW_SWITCH_TRACE_ERR_MASK) || reg))
		return;

	if (pcp_hp_stat & IOB_XGIC_ERR_MASK)
		xgene_edac_iob_gic_report(edac_dev);

	if (pcp_hp_stat & (IOB_RB_ERR_MASK | IOB_BA_ERR_MASK))
		xgene_edac_rb_report(edac_dev);

	if (pcp_hp_stat & IOB_PA_ERR_MASK)
		xgene_edac_pa_report(edac_dev);

	if (pcp_lp_stat & CSW_SWITCH_TRACE_ERR_MASK) {
		dev_info(edac_dev->dev,
			 "CSW switch trace correctable memory parity error\n");
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
	}

	if (!reg)
		return;
	if (ctx->version == 1)
		soc_mem_err = soc_mem_err_v1;
	if (!soc_mem_err) {
		dev_err(edac_dev->dev, "SoC memory parity error 0x%08X\n",
			reg);
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
		return;
	}
	for (i = 0; i < 31; i++) {
		if (reg & (1 << i)) {
			dev_err(edac_dev->dev, "%s memory parity error\n",
				soc_mem_err[i]);
			edac_device_handle_ue(edac_dev, 0, 0,
					      edac_dev->ctl_name);
		}
	}
}