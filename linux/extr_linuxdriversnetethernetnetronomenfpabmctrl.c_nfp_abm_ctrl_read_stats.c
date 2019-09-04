#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct nfp_alink_stats {int /*<<< orphan*/  overlimits; int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog_pkts; int /*<<< orphan*/  backlog_bytes; void* tx_bytes; void* tx_pkts; } ;
struct nfp_abm_link {TYPE_1__* abm; TYPE_2__* vnic; } ;
struct TYPE_4__ {int max_rx_rings; } ;
struct TYPE_3__ {int /*<<< orphan*/  qm_stats; int /*<<< orphan*/  q_lvls; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_RXR_STATS (int) ; 
 int /*<<< orphan*/  NFP_QLVL_BLOG_BYTES ; 
 int /*<<< orphan*/  NFP_QLVL_BLOG_PKTS ; 
 int /*<<< orphan*/  NFP_QLVL_STRIDE ; 
 int /*<<< orphan*/  NFP_QMSTAT_DROP ; 
 int /*<<< orphan*/  NFP_QMSTAT_ECN ; 
 int /*<<< orphan*/  NFP_QMSTAT_STRIDE ; 
 int nfp_abm_ctrl_stat_all (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nn_readq (TYPE_2__*,scalar_t__) ; 

int nfp_abm_ctrl_read_stats(struct nfp_abm_link *alink,
			    struct nfp_alink_stats *stats)
{
	u64 pkts = 0, bytes = 0;
	int i, err;

	for (i = 0; i < alink->vnic->max_rx_rings; i++) {
		pkts += nn_readq(alink->vnic, NFP_NET_CFG_RXR_STATS(i));
		bytes += nn_readq(alink->vnic, NFP_NET_CFG_RXR_STATS(i) + 8);
	}
	stats->tx_pkts = pkts;
	stats->tx_bytes = bytes;

	err = nfp_abm_ctrl_stat_all(alink, alink->abm->q_lvls,
				    NFP_QLVL_STRIDE, NFP_QLVL_BLOG_BYTES,
				    false, &stats->backlog_bytes);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat_all(alink, alink->abm->q_lvls,
				    NFP_QLVL_STRIDE, NFP_QLVL_BLOG_PKTS,
				    false, &stats->backlog_pkts);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat_all(alink, alink->abm->qm_stats,
				    NFP_QMSTAT_STRIDE, NFP_QMSTAT_DROP,
				    true, &stats->drops);
	if (err)
		return err;

	return nfp_abm_ctrl_stat_all(alink, alink->abm->qm_stats,
				     NFP_QMSTAT_STRIDE, NFP_QMSTAT_ECN,
				     true, &stats->overlimits);
}