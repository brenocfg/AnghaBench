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
struct mvpp2_prs_entry {int index; } ;
struct mvpp2_port {int id; int /*<<< orphan*/  priv; } ;
typedef  int /*<<< orphan*/  pe ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_PE_FIRST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PE_LAST_FREE_TID ; 
 int /*<<< orphan*/  MVPP2_PRS_FLOW_ID_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_FLOWS ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_LU_DONE_BIT ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int mvpp2_prs_flow_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (int /*<<< orphan*/ ,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (int /*<<< orphan*/ ,struct mvpp2_prs_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ai_update (struct mvpp2_prs_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int mvpp2_prs_tcam_first_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int) ; 

int mvpp2_prs_def_flow(struct mvpp2_port *port)
{
	struct mvpp2_prs_entry pe;
	int tid;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_prs_flow_find(port->priv, port->id);

	/* Such entry not exist */
	if (tid < 0) {
		/* Go through the all entires from last to first */
		tid = mvpp2_prs_tcam_first_free(port->priv,
						MVPP2_PE_LAST_FREE_TID,
					       MVPP2_PE_FIRST_FREE_TID);
		if (tid < 0)
			return tid;

		pe.index = tid;

		/* Set flow ID*/
		mvpp2_prs_sram_ai_update(&pe, port->id, MVPP2_PRS_FLOW_ID_MASK);
		mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_DONE_BIT, 1);

		/* Update shadow table */
		mvpp2_prs_shadow_set(port->priv, pe.index, MVPP2_PRS_LU_FLOWS);
	} else {
		mvpp2_prs_init_from_hw(port->priv, &pe, tid);
	}

	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_FLOWS);
	mvpp2_prs_tcam_port_map_set(&pe, (1 << port->id));
	mvpp2_prs_hw_write(port->priv, &pe);

	return 0;
}