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
typedef  scalar_t__ u64 ;
struct nfp_abm_link {unsigned int queue_base; TYPE_1__* abm; int /*<<< orphan*/  vnic; } ;
struct TYPE_2__ {int /*<<< orphan*/  q_stats; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_RXR_STATS (unsigned int) ; 
 int /*<<< orphan*/  NFP_Q_STAT_STRIDE ; 
 int nfp_abm_ctrl_stat (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int,scalar_t__*) ; 
 int /*<<< orphan*/  nfp_abm_has_prio (TYPE_1__*) ; 
 scalar_t__ nn_readq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nfp_abm_ctrl_stat_basic(struct nfp_abm_link *alink, unsigned int band,
			unsigned int queue, unsigned int off, u64 *val)
{
	if (!nfp_abm_has_prio(alink->abm)) {
		if (!band) {
			unsigned int id = alink->queue_base + queue;

			*val = nn_readq(alink->vnic,
					NFP_NET_CFG_RXR_STATS(id) + off);
		} else {
			*val = 0;
		}

		return 0;
	} else {
		return nfp_abm_ctrl_stat(alink, alink->abm->q_stats,
					 NFP_Q_STAT_STRIDE, off, band, queue,
					 true, val);
	}
}