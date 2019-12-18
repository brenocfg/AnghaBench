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
struct nfp_abm_link {TYPE_1__* abm; } ;
struct TYPE_2__ {unsigned int num_bands; int /*<<< orphan*/  qm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_QMSTAT_STO ; 
 int /*<<< orphan*/  NFP_QMSTAT_STRIDE ; 
 scalar_t__ nfp_abm_ctrl_stat (struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int,scalar_t__*) ; 

u64 nfp_abm_ctrl_stat_sto(struct nfp_abm_link *alink, unsigned int queue)
{
	unsigned int band;
	u64 val, sum = 0;

	for (band = 0; band < alink->abm->num_bands; band++) {
		if (nfp_abm_ctrl_stat(alink, alink->abm->qm_stats,
				      NFP_QMSTAT_STRIDE, NFP_QMSTAT_STO,
				      band, queue, true, &val))
			return 0;
		sum += val;
	}

	return sum;
}