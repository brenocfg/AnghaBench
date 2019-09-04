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
struct nfp_alink_stats {int /*<<< orphan*/  overlimits; int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog_pkts; int /*<<< orphan*/  backlog_bytes; void* tx_bytes; void* tx_pkts; } ;
struct nfp_abm_link {TYPE_1__* abm; int /*<<< orphan*/  vnic; } ;
struct TYPE_2__ {int /*<<< orphan*/  qm_stats; int /*<<< orphan*/  q_lvls; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_RXR_STATS (unsigned int) ; 
 int /*<<< orphan*/  NFP_QLVL_BLOG_BYTES ; 
 int /*<<< orphan*/  NFP_QLVL_BLOG_PKTS ; 
 int /*<<< orphan*/  NFP_QLVL_STRIDE ; 
 int /*<<< orphan*/  NFP_QMSTAT_DROP ; 
 int /*<<< orphan*/  NFP_QMSTAT_ECN ; 
 int /*<<< orphan*/  NFP_QMSTAT_STRIDE ; 
 int nfp_abm_ctrl_stat (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *) ; 
 void* nn_readq (int /*<<< orphan*/ ,scalar_t__) ; 

int nfp_abm_ctrl_read_q_stats(struct nfp_abm_link *alink, unsigned int i,
			      struct nfp_alink_stats *stats)
{
	int err;

	stats->tx_pkts = nn_readq(alink->vnic, NFP_NET_CFG_RXR_STATS(i));
	stats->tx_bytes = nn_readq(alink->vnic, NFP_NET_CFG_RXR_STATS(i) + 8);

	err = nfp_abm_ctrl_stat(alink, alink->abm->q_lvls,
				NFP_QLVL_STRIDE, NFP_QLVL_BLOG_BYTES,
				i, false, &stats->backlog_bytes);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->q_lvls,
				NFP_QLVL_STRIDE, NFP_QLVL_BLOG_PKTS,
				i, false, &stats->backlog_pkts);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				NFP_QMSTAT_STRIDE, NFP_QMSTAT_DROP,
				i, true, &stats->drops);
	if (err)
		return err;

	return nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				 NFP_QMSTAT_STRIDE, NFP_QMSTAT_ECN,
				 i, true, &stats->overlimits);
}