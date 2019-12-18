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
 int /*<<< orphan*/  MVPP2_PE_VID_EDSA_FLTR_DEFAULT ; 
 int /*<<< orphan*/  MVPP2_PE_VID_FLTR_DEFAULT ; 
 int /*<<< orphan*/  MVPP2_PRS_EDSA_VID_AI_BIT ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_L2 ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_VID ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_AI_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 int /*<<< orphan*/  MVPP2_VLAN_TAG_EDSA_LEN ; 
 int /*<<< orphan*/  MVPP2_VLAN_TAG_LEN ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_prs_vid_init(struct mvpp2 *priv)
{
	struct mvpp2_prs_entry pe;

	memset(&pe, 0, sizeof(pe));

	/* Set default vid entry */
	pe.index = MVPP2_PE_VID_FLTR_DEFAULT;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);

	mvpp2_prs_tcam_ai_update(&pe, 0, MVPP2_PRS_EDSA_VID_AI_BIT);

	/* Skip VLAN header - Set offset to 4 bytes */
	mvpp2_prs_sram_shift_set(&pe, MVPP2_VLAN_TAG_LEN,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Clear all ai bits for next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shadow table and hw entry */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_write(priv, &pe);

	/* Set default vid entry for extended DSA*/
	memset(&pe, 0, sizeof(pe));

	/* Set default vid entry */
	pe.index = MVPP2_PE_VID_EDSA_FLTR_DEFAULT;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);

	mvpp2_prs_tcam_ai_update(&pe, MVPP2_PRS_EDSA_VID_AI_BIT,
				 MVPP2_PRS_EDSA_VID_AI_BIT);

	/* Skip VLAN header - Set offset to 8 bytes */
	mvpp2_prs_sram_shift_set(&pe, MVPP2_VLAN_TAG_EDSA_LEN,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Clear all ai bits for next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shadow table and hw entry */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_write(priv, &pe);
}