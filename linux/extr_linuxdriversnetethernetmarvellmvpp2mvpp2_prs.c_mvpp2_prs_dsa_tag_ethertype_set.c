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
struct mvpp2 {TYPE_1__* prs_shadow; } ;
typedef  int /*<<< orphan*/  pe ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_EDSA ; 
 scalar_t__ MVPP2_ETH_TYPE_LEN ; 
 int MVPP2_PE_ETYPE_DSA_TAGGED ; 
 int MVPP2_PE_ETYPE_DSA_UNTAGGED ; 
 int MVPP2_PE_ETYPE_EDSA_TAGGED ; 
 int MVPP2_PE_ETYPE_EDSA_UNTAGGED ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_DSA ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_L2 ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_VLAN ; 
 int MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_DSA_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_VLAN_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_VLAN_NONE ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_AI_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 int /*<<< orphan*/  MVPP2_PRS_TCAM_DSA_TAGGED_BIT ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_prs_match_etype (struct mvpp2_prs_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_set (struct mvpp2_prs_entry*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_set (struct mvpp2_prs_entry*,int,int) ; 

__attribute__((used)) static void mvpp2_prs_dsa_tag_ethertype_set(struct mvpp2 *priv, int port,
					    bool add, bool tagged, bool extend)
{
	struct mvpp2_prs_entry pe;
	int tid, shift, port_mask;

	if (extend) {
		tid = tagged ? MVPP2_PE_ETYPE_EDSA_TAGGED :
		      MVPP2_PE_ETYPE_EDSA_UNTAGGED;
		port_mask = 0;
		shift = 8;
	} else {
		tid = tagged ? MVPP2_PE_ETYPE_DSA_TAGGED :
		      MVPP2_PE_ETYPE_DSA_UNTAGGED;
		port_mask = MVPP2_PRS_PORT_MASK;
		shift = 4;
	}

	if (priv->prs_shadow[tid].valid) {
		/* Entry exist - update port only */
		mvpp2_prs_init_from_hw(priv, &pe, tid);
	} else {
		/* Entry doesn't exist - create new */
		memset(&pe, 0, sizeof(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_DSA);
		pe.index = tid;

		/* Set ethertype */
		mvpp2_prs_match_etype(&pe, 0, ETH_P_EDSA);
		mvpp2_prs_match_etype(&pe, 2, 0);

		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DSA_MASK,
					 MVPP2_PRS_RI_DSA_MASK);
		/* Shift ethertype + 2 byte reserved + tag*/
		mvpp2_prs_sram_shift_set(&pe, 2 + MVPP2_ETH_TYPE_LEN + shift,
					 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

		/* Update shadow table */
		mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_DSA);

		if (tagged) {
			/* Set tagged bit in DSA tag */
			mvpp2_prs_tcam_data_byte_set(&pe,
						     MVPP2_ETH_TYPE_LEN + 2 + 3,
						 MVPP2_PRS_TCAM_DSA_TAGGED_BIT,
						 MVPP2_PRS_TCAM_DSA_TAGGED_BIT);
			/* Clear all ai bits for next iteration */
			mvpp2_prs_sram_ai_update(&pe, 0,
						 MVPP2_PRS_SRAM_AI_MASK);
			/* If packet is tagged continue check vlans */
			mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VLAN);
		} else {
			/* Set result info bits to 'no vlans' */
			mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_VLAN_NONE,
						 MVPP2_PRS_RI_VLAN_MASK);
			mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);
		}
		/* Mask/unmask all ports, depending on dsa type */
		mvpp2_prs_tcam_port_map_set(&pe, port_mask);
	}

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port, add);

	mvpp2_prs_hw_write(priv, &pe);
}