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
 unsigned int MVPP2_PRS_DBL_VLAN_AI_BIT ; 
 scalar_t__ MVPP2_PRS_LU_VLAN ; 
 unsigned int MVPP2_PRS_RI_VLAN_MASK ; 
 unsigned int MVPP2_PRS_RI_VLAN_SINGLE ; 
 unsigned int MVPP2_PRS_RI_VLAN_TRIPLE ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 unsigned int mvpp2_prs_sram_ri_get (struct mvpp2_prs_entry*) ; 
 unsigned int mvpp2_prs_tcam_ai_get (struct mvpp2_prs_entry*) ; 
 int mvpp2_prs_tcam_data_cmp (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int mvpp2_prs_vlan_find(struct mvpp2 *priv, unsigned short tpid, int ai)
{
	struct mvpp2_prs_entry pe;
	int tid;

	/* Go through the all entries with MVPP2_PRS_LU_VLAN */
	for (tid = MVPP2_PE_FIRST_FREE_TID;
	     tid <= MVPP2_PE_LAST_FREE_TID; tid++) {
		unsigned int ri_bits, ai_bits;
		bool match;

		if (!priv->prs_shadow[tid].valid ||
		    priv->prs_shadow[tid].lu != MVPP2_PRS_LU_VLAN)
			continue;

		mvpp2_prs_init_from_hw(priv, &pe, tid);
		match = mvpp2_prs_tcam_data_cmp(&pe, 0, tpid);
		if (!match)
			continue;

		/* Get vlan type */
		ri_bits = mvpp2_prs_sram_ri_get(&pe);
		ri_bits &= MVPP2_PRS_RI_VLAN_MASK;

		/* Get current ai value from tcam */
		ai_bits = mvpp2_prs_tcam_ai_get(&pe);
		/* Clear double vlan bit */
		ai_bits &= ~MVPP2_PRS_DBL_VLAN_AI_BIT;

		if (ai != ai_bits)
			continue;

		if (ri_bits == MVPP2_PRS_RI_VLAN_SINGLE ||
		    ri_bits == MVPP2_PRS_RI_VLAN_TRIPLE)
			return tid;
	}

	return -ENOENT;
}