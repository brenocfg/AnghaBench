#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mvpp2_prs_entry {int /*<<< orphan*/  index; } ;
struct mvpp2 {int dummy; } ;
typedef  int /*<<< orphan*/  pe ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_PE_DSA_DEFAULT ; 
 int /*<<< orphan*/  MVPP2_PRS_DSA ; 
 int /*<<< orphan*/  MVPP2_PRS_EDSA ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_DSA ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_MAC ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_VLAN ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_AI_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 int /*<<< orphan*/  MVPP2_PRS_TAGGED ; 
 int /*<<< orphan*/  MVPP2_PRS_UNTAGGED ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_dsa_tag_ethertype_set (struct mvpp2*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_dsa_tag_set (struct mvpp2*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_prs_dsa_init(struct mvpp2 *priv)
{
	struct mvpp2_prs_entry pe;

	/* None tagged EDSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_UNTAGGED,
			      MVPP2_PRS_EDSA);

	/* Tagged EDSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);

	/* None tagged DSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_UNTAGGED,
			      MVPP2_PRS_DSA);

	/* Tagged DSA entry - place holder */
	mvpp2_prs_dsa_tag_set(priv, 0, false, MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);

	/* None tagged EDSA ethertype entry - place holder*/
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, false,
					MVPP2_PRS_UNTAGGED, MVPP2_PRS_EDSA);

	/* Tagged EDSA ethertype entry - place holder*/
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, false,
					MVPP2_PRS_TAGGED, MVPP2_PRS_EDSA);

	/* None tagged DSA ethertype entry */
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, true,
					MVPP2_PRS_UNTAGGED, MVPP2_PRS_DSA);

	/* Tagged DSA ethertype entry */
	mvpp2_prs_dsa_tag_ethertype_set(priv, 0, true,
					MVPP2_PRS_TAGGED, MVPP2_PRS_DSA);

	/* Set default entry, in case DSA or EDSA tag not found */
	memset(&pe, 0, sizeof(pe));
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_DSA);
	pe.index = MVPP2_PE_DSA_DEFAULT;
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_VLAN);

	/* Shift 0 bytes */
	mvpp2_prs_sram_shift_set(&pe, 0, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_MAC);

	/* Clear all sram ai bits for next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	mvpp2_prs_hw_write(priv, &pe);
}