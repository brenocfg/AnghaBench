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
 int /*<<< orphan*/  MVPP2_MH_SIZE ; 
 int /*<<< orphan*/  MVPP2_PE_MH_DEFAULT ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_MAC ; 
 int /*<<< orphan*/  MVPP2_PRS_LU_MH ; 
 int /*<<< orphan*/  MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_write (struct mvpp2*,struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  mvpp2_prs_shadow_set (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_next_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_shift_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_lu_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_tcam_port_map_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_prs_mh_init(struct mvpp2 *priv)
{
	struct mvpp2_prs_entry pe;

	memset(&pe, 0, sizeof(pe));

	pe.index = MVPP2_PE_MH_DEFAULT;
	mvpp2_prs_tcam_lu_set(&pe, MVPP2_PRS_LU_MH);
	mvpp2_prs_sram_shift_set(&pe, MVPP2_MH_SIZE,
				 MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD);
	mvpp2_prs_sram_next_lu_set(&pe, MVPP2_PRS_LU_MAC);

	/* Unmask all ports */
	mvpp2_prs_tcam_port_map_set(&pe, MVPP2_PRS_PORT_MASK);

	/* Update shadow table and hw entry */
	mvpp2_prs_shadow_set(priv, pe.index, MVPP2_PRS_LU_MH);
	mvpp2_prs_hw_write(priv, &pe);
}