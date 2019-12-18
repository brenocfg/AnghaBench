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
 int /*<<< orphan*/  MVPP2_PE_MAC_NON_PROMISCUOUS ; 
 int /*<<< orphan*/  MVPP2_PRS_L2_MULTI_CAST ; 
 int /*<<< orphan*/  MVPP2_PRS_L2_UNI_CAST ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_FLOWS ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_MAC ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_RI_DROP_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_LU_GEN_BIT ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_mac_drop_all_set (struct mvpp2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_mac_promisc_set (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_ri_update (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_prs_mac_init(struct mvpp2 *priv)
{
	struct mvpp2_prs_entry pe;

	memset(&pe, 0, sizeof(pe));

	/* Non-promiscuous mode for all ports - DROP unknown packets */
	pe.index = MVPP2_PE_MAC_NON_PROMISCUOUS;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MAC);

	mvpp2_prs_sram_ri_update(&pe, MVPP2_PRS_RI_DROP_MASK,
				 MVPP2_PRS_RI_DROP_MASK);
	mvpp2_prs_sram_bits_set(&pe, MVPP2_PRS_SRAM_LU_GEN_BIT, 1);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_FLOWS);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shadow table and hw entry */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_MAC);
	mvpp2_prs_hw_write(priv, &pe);

	/* Create dummy entries for drop all and promiscuous modes */
	mvpp2_prs_mac_drop_all_set(priv, 0, false);
	mvpp2_prs_mac_promisc_set(priv, 0, MVPP2_PRS_L2_UNI_CAST, false);
	mvpp2_prs_mac_promisc_set(priv, 0, MVPP2_PRS_L2_MULTI_CAST, false);
}