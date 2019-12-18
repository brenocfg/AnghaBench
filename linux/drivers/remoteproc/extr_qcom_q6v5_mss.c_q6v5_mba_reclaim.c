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
struct q6v5 {int dump_mba_loaded; scalar_t__ version; int /*<<< orphan*/  proxy_reg_count; int /*<<< orphan*/  proxy_regs; int /*<<< orphan*/  proxy_clk_count; int /*<<< orphan*/  proxy_clks; int /*<<< orphan*/  dev; int /*<<< orphan*/  proxy_pd_count; int /*<<< orphan*/  proxy_pds; int /*<<< orphan*/  q6v5; int /*<<< orphan*/  mba_size; int /*<<< orphan*/  mba_phys; int /*<<< orphan*/  mba_perm; int /*<<< orphan*/  active_pd_count; int /*<<< orphan*/  active_pds; int /*<<< orphan*/  active_reg_count; int /*<<< orphan*/  active_regs; int /*<<< orphan*/  active_clk_count; int /*<<< orphan*/  active_clks; int /*<<< orphan*/  reset_clk_count; int /*<<< orphan*/  reset_clks; int /*<<< orphan*/  mpss_size; int /*<<< orphan*/  mpss_phys; int /*<<< orphan*/  mpss_perm; scalar_t__ reg_base; int /*<<< orphan*/  halt_nc; int /*<<< orphan*/  halt_map; int /*<<< orphan*/  halt_modem; int /*<<< orphan*/  halt_q6; } ;

/* Variables and functions */
 scalar_t__ MSS_MSM8996 ; 
 int Q6SS_CLAMP_IO ; 
 scalar_t__ QDSP6SS_PWR_CTL_REG ; 
 int QDSP6v56_CLAMP_QMC_MEM ; 
 int QDSP6v56_CLAMP_WL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  q6v5_clk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_pds_disable (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_regulator_disable (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_reset_assert (struct q6v5*) ; 
 int q6v5_xfer_mem_ownership (struct q6v5*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5proc_halt_axi_port (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qcom_q6v5_unprepare (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void q6v5_mba_reclaim(struct q6v5 *qproc)
{
	int ret;
	u32 val;

	qproc->dump_mba_loaded = false;

	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_q6);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_modem);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_nc);
	if (qproc->version == MSS_MSM8996) {
		/*
		 * To avoid high MX current during LPASS/MSS restart.
		 */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_CLAMP_IO | QDSP6v56_CLAMP_WL |
			QDSP6v56_CLAMP_QMC_MEM;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	}

	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm,
				      false, qproc->mpss_phys,
				      qproc->mpss_size);
	WARN_ON(ret);

	q6v5_reset_assert(qproc);

	q6v5_clk_disable(qproc->dev, qproc->reset_clks,
			 qproc->reset_clk_count);
	q6v5_clk_disable(qproc->dev, qproc->active_clks,
			 qproc->active_clk_count);
	q6v5_regulator_disable(qproc, qproc->active_regs,
			       qproc->active_reg_count);
	q6v5_pds_disable(qproc, qproc->active_pds, qproc->active_pd_count);

	/* In case of failure or coredump scenario where reclaiming MBA memory
	 * could not happen reclaim it here.
	 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, false,
				      qproc->mba_phys,
				      qproc->mba_size);
	WARN_ON(ret);

	ret = qcom_q6v5_unprepare(&qproc->q6v5);
	if (ret) {
		q6v5_pds_disable(qproc, qproc->proxy_pds,
				 qproc->proxy_pd_count);
		q6v5_clk_disable(qproc->dev, qproc->proxy_clks,
				 qproc->proxy_clk_count);
		q6v5_regulator_disable(qproc, qproc->proxy_regs,
				       qproc->proxy_reg_count);
	}
}