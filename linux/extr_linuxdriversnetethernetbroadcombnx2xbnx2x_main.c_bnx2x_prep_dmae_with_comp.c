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
struct dmae_command {int /*<<< orphan*/  comp_val; int /*<<< orphan*/  comp_addr_hi; int /*<<< orphan*/  comp_addr_lo; int /*<<< orphan*/  opcode; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAE_COMP_PCI ; 
 int /*<<< orphan*/  DMAE_COMP_VAL ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dmae_opcode (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dmae_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_comp ; 

void bnx2x_prep_dmae_with_comp(struct bnx2x *bp,
				      struct dmae_command *dmae,
				      u8 src_type, u8 dst_type)
{
	memset(dmae, 0, sizeof(struct dmae_command));

	/* set the opcode */
	dmae->opcode = bnx2x_dmae_opcode(bp, src_type, dst_type,
					 true, DMAE_COMP_PCI);

	/* fill in the completion parameters */
	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, wb_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, wb_comp));
	dmae->comp_val = DMAE_COMP_VAL;
}