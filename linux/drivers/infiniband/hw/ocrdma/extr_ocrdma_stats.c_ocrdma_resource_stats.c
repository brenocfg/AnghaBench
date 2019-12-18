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
typedef  int /*<<< orphan*/  u64 ;
struct ocrdma_rsrc_stats {scalar_t__ mw; scalar_t__ phy_mr; scalar_t__ ondemand_qps; scalar_t__ prefetch_qps; scalar_t__ frmr; scalar_t__ embedded_nsmr; scalar_t__ r128G_to_higher_nsmr; scalar_t__ r64G_to_128G_nsmr; scalar_t__ r32G_to_64G_nsmr; scalar_t__ nsmr_count_4G_to_32G; scalar_t__ r1G_to_4G_nsmr; scalar_t__ r44M_to_1G_nsmr; scalar_t__ r2M_to_44M_nsmr; scalar_t__ r64K_to_2M_nsmr; scalar_t__ r64K_nsmr; scalar_t__ rbqs; scalar_t__ srqs; scalar_t__ ud_non_dpp_qps; scalar_t__ uc_non_dpp_qps; scalar_t__ rc_non_dpp_qps; scalar_t__ ud_dpp_qps; scalar_t__ uc_dpp_qps; scalar_t__ rc_dpp_qps; scalar_t__ non_dpp_pds; scalar_t__ dpp_pds; } ;
struct ocrdma_rdma_stats_resp {struct ocrdma_rsrc_stats th_rsrc_stats; struct ocrdma_rsrc_stats act_rsrc_stats; } ;
struct TYPE_2__ {char* debugfs_mem; scalar_t__ va; } ;
struct ocrdma_dev {TYPE_1__ stats_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_MAX_DBGFS_MEM ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_add_stat (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ocrdma_resource_stats(struct ocrdma_dev *dev)
{
	char *stats = dev->stats_mem.debugfs_mem, *pcur;
	struct ocrdma_rdma_stats_resp *rdma_stats =
			(struct ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	struct ocrdma_rsrc_stats *rsrc_stats = &rdma_stats->act_rsrc_stats;

	memset(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "active_dpp_pds",
				(u64)rsrc_stats->dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "active_non_dpp_pds",
				(u64)rsrc_stats->non_dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "active_rc_dpp_qps",
				(u64)rsrc_stats->rc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_uc_dpp_qps",
				(u64)rsrc_stats->uc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_ud_dpp_qps",
				(u64)rsrc_stats->ud_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_rc_non_dpp_qps",
				(u64)rsrc_stats->rc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_uc_non_dpp_qps",
				(u64)rsrc_stats->uc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_ud_non_dpp_qps",
				(u64)rsrc_stats->ud_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_srqs",
				(u64)rsrc_stats->srqs);
	pcur += ocrdma_add_stat(stats, pcur, "active_rbqs",
				(u64)rsrc_stats->rbqs);
	pcur += ocrdma_add_stat(stats, pcur, "active_64K_nsmr",
				(u64)rsrc_stats->r64K_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_64K_to_2M_nsmr",
				(u64)rsrc_stats->r64K_to_2M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_2M_to_44M_nsmr",
				(u64)rsrc_stats->r2M_to_44M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_44M_to_1G_nsmr",
				(u64)rsrc_stats->r44M_to_1G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_1G_to_4G_nsmr",
				(u64)rsrc_stats->r1G_to_4G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_nsmr_count_4G_to_32G",
				(u64)rsrc_stats->nsmr_count_4G_to_32G);
	pcur += ocrdma_add_stat(stats, pcur, "active_32G_to_64G_nsmr",
				(u64)rsrc_stats->r32G_to_64G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_64G_to_128G_nsmr",
				(u64)rsrc_stats->r64G_to_128G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_128G_to_higher_nsmr",
				(u64)rsrc_stats->r128G_to_higher_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_embedded_nsmr",
				(u64)rsrc_stats->embedded_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_frmr",
				(u64)rsrc_stats->frmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_prefetch_qps",
				(u64)rsrc_stats->prefetch_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_ondemand_qps",
				(u64)rsrc_stats->ondemand_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_phy_mr",
				(u64)rsrc_stats->phy_mr);
	pcur += ocrdma_add_stat(stats, pcur, "active_mw",
				(u64)rsrc_stats->mw);

	/* Print the threshold stats */
	rsrc_stats = &rdma_stats->th_rsrc_stats;

	pcur += ocrdma_add_stat(stats, pcur, "threshold_dpp_pds",
				(u64)rsrc_stats->dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_non_dpp_pds",
				(u64)rsrc_stats->non_dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_rc_dpp_qps",
				(u64)rsrc_stats->rc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_uc_dpp_qps",
				(u64)rsrc_stats->uc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_ud_dpp_qps",
				(u64)rsrc_stats->ud_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_rc_non_dpp_qps",
				(u64)rsrc_stats->rc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_uc_non_dpp_qps",
				(u64)rsrc_stats->uc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_ud_non_dpp_qps",
				(u64)rsrc_stats->ud_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_srqs",
				(u64)rsrc_stats->srqs);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_rbqs",
				(u64)rsrc_stats->rbqs);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_64K_nsmr",
				(u64)rsrc_stats->r64K_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_64K_to_2M_nsmr",
				(u64)rsrc_stats->r64K_to_2M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_2M_to_44M_nsmr",
				(u64)rsrc_stats->r2M_to_44M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_44M_to_1G_nsmr",
				(u64)rsrc_stats->r44M_to_1G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_1G_to_4G_nsmr",
				(u64)rsrc_stats->r1G_to_4G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_nsmr_count_4G_to_32G",
				(u64)rsrc_stats->nsmr_count_4G_to_32G);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_32G_to_64G_nsmr",
				(u64)rsrc_stats->r32G_to_64G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_64G_to_128G_nsmr",
				(u64)rsrc_stats->r64G_to_128G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_128G_to_higher_nsmr",
				(u64)rsrc_stats->r128G_to_higher_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_embedded_nsmr",
				(u64)rsrc_stats->embedded_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_frmr",
				(u64)rsrc_stats->frmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_prefetch_qps",
				(u64)rsrc_stats->prefetch_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_ondemand_qps",
				(u64)rsrc_stats->ondemand_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_phy_mr",
				(u64)rsrc_stats->phy_mr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_mw",
				(u64)rsrc_stats->mw);
	return stats;
}