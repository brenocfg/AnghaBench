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
struct mvpp2_prs_entry {int index; } ;
struct mvpp2 {int* prs_double_vlans; TYPE_1__* prs_shadow; } ;
typedef  int /*<<< orphan*/  pe ;
struct TYPE_2__ {scalar_t__ lu; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int ERANGE ; 
 int MVPP2_PE_FIRST_FREE_TID ; 
 int MVPP2_PE_LAST_FREE_TID ; 
 int MVPP2_PRS_DBL_VLAN_AI_BIT ; 
 scalar_t__ MVPP2_PRS_LU_VLAN ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_VLAN_DOUBLE ; 
 unsigned int MVPP2_PRS_RI_VLAN_MASK ; 
 unsigned int MVPP2_PRS_RI_VLAN_SINGLE ; 
 unsigned int MVPP2_PRS_RI_VLAN_TRIPLE ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_AI_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 int /*<<< orphan*/  MVPP2_VLAN_TAG_LEN ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int mvpp2_prs_double_vlan_ai_free_get (struct mvpp2*) ; 
 int mvpp2_prs_double_vlan_find (struct mvpp2*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_prs_match_etype (struct mvpp2_prs_entry*,int,unsigned short) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int,scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,scalar_t__) ; 
 unsigned int mvpp2_prs_sram_ri_get (struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mvpp2_prs_tcam_first_free (struct mvpp2*,int,int) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,unsigned int) ; 

__attribute__((used)) static int mvpp2_prs_double_vlan_add(struct mvpp2 *priv, unsigned short tpid1,
				     unsigned short tpid2,
				     unsigned int port_map)
{
	int tid_aux, tid, ai, ret = 0;
	struct mvpp2_prs_entry pe;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_prs_double_vlan_find(priv, tpid1, tpid2);

	if (tid < 0) {
		/* Create new tcam entry */
		tid = mvpp2_prs_tcam_first_free(priv, MVPP2_PE_FIRST_FREE_TID,
				MVPP2_PE_LAST_FREE_TID);
		if (tid < 0)
			return tid;

		/* Set ai value for new double vlan entry */
		ai = mvpp2_prs_double_vlan_ai_free_get(priv);
		if (ai < 0)
			return ai;

		/* Get first single/triple vlan tid */
		for (tid_aux = MVPP2_PE_FIRST_FREE_TID;
		     tid_aux <= MVPP2_PE_LAST_FREE_TID; tid_aux++) {
			unsigned int ri_bits;

			if (!priv->prs_shadow[tid_aux].valid ||
			    priv->prs_shadow[tid_aux].lu != MVPP2_PRS_LU_VLAN)
				continue;

			mvpp2_prs_init_from_hw(priv, &pe, tid_aux);
			ri_bits = mvpp2_prs_sram_ri_get(&pe);
			ri_bits &= MVPP2_PRS_RI_VLAN_MASK;
			if (ri_bits == MVPP2_PRS_RI_VLAN_SINGLE ||
			    ri_bits == MVPP2_PRS_RI_VLAN_TRIPLE)
				break;
		}

		if (tid >= tid_aux)
			return -ERANGE;

		memset(&pe, 0, sizeof(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VLAN);
		pe.index = tid;

		priv->prs_double_vlans[ai] = true;

		mvpp2_prs_match_etype(&pe, 0, tpid1);
		mvpp2_prs_match_etype(&pe, 4, tpid2);

		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VLAN);
		/* Shift 4 bytes - skip outer vlan tag */
		mvpp2_prs_sram_shift_set(&pe, MVPP2_VLAN_TAG_LEN,
					 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_DOUBLE,
					 MVPP2_PRS_RI_VLAN_MASK);
		mvpp2_prs_sram_ai_update(&pe, ai | MVPP2_PRS_DBL_VLAN_AI_BIT,
					 MVPP2_PRS_SRAM_AI_MASK);

		mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_VLAN);
	} else {
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	}

	/* Update ports' mask */
	mvpp2_prs_tcam_port_map_set(&pe, port_map);
	mvpp2_prs_hw_write(priv, &pe);

	return ret;
}