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
typedef  size_t u16 ;
struct rvu {int dummy; } ;
struct TYPE_2__ {size_t max; } ;
struct npc_mcam {size_t* cntr2pfvf_map; TYPE_1__ counters; scalar_t__* cntr_refcnt; } ;

/* Variables and functions */
 size_t NPC_MCAM_INVALID_MAP ; 
 int /*<<< orphan*/  rvu_free_rsrc (TYPE_1__*,size_t) ; 

__attribute__((used)) static void npc_mcam_free_all_counters(struct rvu *rvu, struct npc_mcam *mcam,
				       u16 pcifunc)
{
	u16 cntr;

	/* Scan all MCAM counters and free the ones mapped to 'pcifunc' */
	for (cntr = 0; cntr < mcam->counters.max; cntr++) {
		if (mcam->cntr2pfvf_map[cntr] == pcifunc) {
			mcam->cntr2pfvf_map[cntr] = NPC_MCAM_INVALID_MAP;
			mcam->cntr_refcnt[cntr] = 0;
			rvu_free_rsrc(&mcam->counters, cntr);
			/* This API is expected to be called after freeing
			 * MCAM entries, which inturn will remove
			 * 'entry to counter' mapping.
			 * No need to do it again.
			 */
		}
	}
}