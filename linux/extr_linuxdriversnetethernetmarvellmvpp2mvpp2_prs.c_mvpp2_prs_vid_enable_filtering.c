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
struct mvpp2_prs_entry {unsigned int index; } ;
struct mvpp2_port {int /*<<< orphan*/  id; struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
typedef  int /*<<< orphan*/  pe ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 unsigned int MVPP2_DSA_EXTENDED ; 
 int /*<<< orphan*/  MVPP2_MH_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_L2 ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_VID ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_DROP_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_AI_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 unsigned int MVPP2_PRS_VID_PORT_DFLT (int /*<<< orphan*/ ) ; 
 unsigned int MVPP2_VLAN_TAG_EDSA_LEN ; 
 unsigned int MVPP2_VLAN_TAG_LEN ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 unsigned int mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 

void mvpp2_prs_vid_enable_filtering(struct mvpp2_port *port)
{
	unsigned int tid = MVPP2_PRS_VID_PORT_DFLT(port->id);
	struct mvpp2 *priv = port->priv;
	unsigned int reg_val, shift;
	struct mvpp2_prs_entry pe;

	if (priv->prs_shadow[tid].valid)
		return;

	memset(&pe, 0, sizeof(pe));

	pe.index = tid;

	reg_val = mvpp2_read(priv, MVPP2_MH_REG(port->id));
	if (reg_val & MVPP2_DSA_EXTENDED)
		shift = MVPP2_VLAN_TAG_EDSA_LEN;
	else
		shift = MVPP2_VLAN_TAG_LEN;

	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_VID);

	/* Mask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, 0);

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port->id, true);

	/* Continue - set next lookup */
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_L2);

	/* Skip VLAN header - Set offset to 4 or 8 bytes */
	mvpp2_prs_sram_shift_set(&pe, shift, MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);

	/* Drop VLAN packets that don't belong to any VIDs on this port */
	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
				 MVPP2_PRS_RI_DROP_MASK);

	/* Clear all ai bits for next iteration */
	mvpp2_prs_sram_ai_update(&pe, 0, MVPP2_PRS_SRAM_AI_MASK);

	/* Update shadow table */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_VID);
	mvpp2_prs_hw_write(priv, &pe);
}