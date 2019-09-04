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
struct mvpp2_prs_entry {int dummy; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {scalar_t__ lu; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int ENOENT ; 
 int MVPP2_PE_FIRST_FREE_TID ; 
 int MVPP2_PE_LAST_FREE_TID ; 
 scalar_t__ MVPP2_PRS_LU_VLAN ; 
 unsigned int MVPP2_PRS_RI_VLAN_DOUBLE ; 
 unsigned int MVPP2_PRS_RI_VLAN_MASK ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 unsigned int mvpp2_prs_sram_ri_get (struct mvpp2_prs_entry*) ; 
 scalar_t__ mvpp2_prs_tcam_data_cmp (struct mvpp2_prs_entry*,int,unsigned short) ; 

__attribute__((used)) static int mvpp2_prs_double_vlan_find(struct mvpp2 *priv, unsigned short tpid1,
				      unsigned short tpid2)
{
	struct mvpp2_prs_entry pe;
	int tid;

	/* Go through the all entries with MVPP2_PRS_LU_VLAN */
	for (tid = MVPP2_PE_FIRST_FREE_TID;
	     tid <= MVPP2_PE_LAST_FREE_TID; tid++) {
		unsigned int ri_mask;
		bool match;

		if (!priv->prs_shadow[tid].valid ||
		    priv->prs_shadow[tid].lu != MVPP2_PRS_LU_VLAN)
			continue;

		mvpp2_prs_init_from_hw(priv, &pe, tid);

		match = mvpp2_prs_tcam_data_cmp(&pe, 0, tpid1) &&
			mvpp2_prs_tcam_data_cmp(&pe, 4, tpid2);

		if (!match)
			continue;

		ri_mask = mvpp2_prs_sram_ri_get(&pe) & MVPP2_PRS_RI_VLAN_MASK;
		if (ri_mask == MVPP2_PRS_RI_VLAN_DOUBLE)
			return tid;
	}

	return -ENOENT;
}