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
struct mvpp2_prs_entry {size_t index; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
typedef  int /*<<< orphan*/  pe ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 size_t MVPP2_PE_DROP_ALL ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_FLOWS ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_MAC ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_DROP_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_LU_GEN_BIT ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,size_t) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_set (struct mvpp2_prs_entry*,int,int) ; 

__attribute__((used)) static void mvpp2_prs_mac_drop_all_set(struct mvpp2 *priv, int port, bool add)
{
	struct mvpp2_prs_entry pe;

	if (priv->prs_shadow[MVPP2_PE_DROP_ALL].valid) {
		/* Entry exist - update port only */
		mvpp2_prs_init_from_hw(priv, &pe, MVPP2_PE_DROP_ALL);
	} else {
		/* Entry doesn't exist - create new */
		memset(&pe, 0, sizeof(pe));
		mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);
		pe.index = MVPP2_PE_DROP_ALL;

		/* Non-promiscuous mode for all ports - DROP unknown packets */
		mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
					 MVPP2_PRS_RI_DROP_MASK);

		mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
		mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);

		/* Update shadow table */
		mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_MAC);

		/* Mask all ports */
		mvpp2_prs_tcam_port_map_set(&pe, 0);
	}

	/* Update port mask */
	mvpp2_prs_tcam_port_set(&pe, port, add);

	mvpp2_prs_hw_write(priv, &pe);
}