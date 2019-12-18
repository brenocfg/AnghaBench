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
struct nfp_alink_stats {int /*<<< orphan*/  overlimits; int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog_pkts; int /*<<< orphan*/  backlog_bytes; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_pkts; } ;
struct nfp_abm_link {TYPE_1__* abm; } ;
struct TYPE_2__ {int /*<<< orphan*/  qm_stats; int /*<<< orphan*/  q_lvls; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_QLVL_BLOG_BYTES ; 
 int /*<<< orphan*/  NFP_QLVL_BLOG_PKTS ; 
 int /*<<< orphan*/  NFP_QLVL_STRIDE ; 
 int /*<<< orphan*/  NFP_QMSTAT_DROP ; 
 int /*<<< orphan*/  NFP_QMSTAT_ECN ; 
 int /*<<< orphan*/  NFP_QMSTAT_STRIDE ; 
 int /*<<< orphan*/  NFP_Q_STAT_BYTES ; 
 int /*<<< orphan*/  NFP_Q_STAT_PKTS ; 
 int nfp_abm_ctrl_stat (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ *) ; 
 int nfp_abm_ctrl_stat_basic (struct nfp_abm_link*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfp_abm_ctrl_read_q_stats(struct nfp_abm_link *alink, unsigned int band,
			      unsigned int queue, struct nfp_alink_stats *stats)
{
	int err;

	err = nfp_abm_ctrl_stat_basic(alink, band, queue, NFP_Q_STAT_PKTS,
				      &stats->tx_pkts);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat_basic(alink, band, queue, NFP_Q_STAT_BYTES,
				      &stats->tx_bytes);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->q_lvls, NFP_QLVL_STRIDE,
				NFP_QLVL_BLOG_BYTES, band, queue, false,
				&stats->backlog_bytes);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->q_lvls,
				NFP_QLVL_STRIDE, NFP_QLVL_BLOG_PKTS,
				band, queue, false, &stats->backlog_pkts);
	if (err)
		return err;

	err = nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				NFP_QMSTAT_STRIDE, NFP_QMSTAT_DROP,
				band, queue, true, &stats->drops);
	if (err)
		return err;

	return nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				 NFP_QMSTAT_STRIDE, NFP_QMSTAT_ECN,
				 band, queue, true, &stats->overlimits);
}