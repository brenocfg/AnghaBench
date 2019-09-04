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
struct nfp_alink_xstats {int /*<<< orphan*/  ecn_marked; int /*<<< orphan*/  pdrop; } ;
struct nfp_abm_link {TYPE_1__* abm; } ;
struct TYPE_2__ {int /*<<< orphan*/  qm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_QMSTAT_DROP ; 
 int /*<<< orphan*/  NFP_QMSTAT_ECN ; 
 int /*<<< orphan*/  NFP_QMSTAT_STRIDE ; 
 int nfp_abm_ctrl_stat_all (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int nfp_abm_ctrl_read_xstats(struct nfp_abm_link *alink,
			     struct nfp_alink_xstats *xstats)
{
	int err;

	err = nfp_abm_ctrl_stat_all(alink, alink->abm->qm_stats,
				    NFP_QMSTAT_STRIDE, NFP_QMSTAT_DROP,
				    true, &xstats->pdrop);
	if (err)
		return err;

	return nfp_abm_ctrl_stat_all(alink, alink->abm->qm_stats,
				     NFP_QMSTAT_STRIDE, NFP_QMSTAT_ECN,
				     true, &xstats->ecn_marked);
}