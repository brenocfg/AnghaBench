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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mvpp2_prs_entry {int index; } ;
struct mvpp2 {int dummy; } ;
typedef  int /*<<< orphan*/  pe ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_PE_FIRST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PE_LAST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PRS_FLOW_ID_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_FLOWS ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_LU_DONE_BIT ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_set (struct mvpp2_prs_entry*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mvpp2_prs_tcam_first_free (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

int mvpp2_prs_add_flow(struct mvpp2 *priv, int flow, u32 ri, u32 ri_mask)
{
	struct mvpp2_prs_entry pe;
	u8 *ri_byte, *ri_byte_mask;
	int tid, i;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_prs_tcam_first_free(priv,
					MVPP2_PE_LAST_FREE_TID,
					MVPP2_PE_FIRST_FREE_TID);
	if (tid < 0)
		return tid;

	pe.index = tid;

	ri_byte = (u8 *)&ri;
	ri_byte_mask = (u8 *)&ri_mask;

	mvpp2_prs_sram_ai_update(&pe, flow, MVPP2_PRS_FLOW_ID_MASK);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_DONE_BIT, 1);

	for (i = 0; i < 4; i++) {
		mvpp2_prs_tcam_data_byte_set(&pe, i, ri_byte[i],
					     ri_byte_mask[i]);
	}

	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);
	mvpp2_prs_hw_write(priv, &pe);

	return 0;
}