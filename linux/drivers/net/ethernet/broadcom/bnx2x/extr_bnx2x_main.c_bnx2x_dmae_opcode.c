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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BP_PORT (struct bnx2x*) ; 
 int BP_VN (struct bnx2x*) ; 
 int DMAE_CMD_DST_RESET ; 
 int DMAE_CMD_E1HVN_SHIFT ; 
 int DMAE_CMD_ENDIANITY_B_DW_SWAP ; 
 int DMAE_CMD_ENDIANITY_DW_SWAP ; 
 int DMAE_CMD_PORT_0 ; 
 int DMAE_CMD_PORT_1 ; 
 int DMAE_CMD_SRC_RESET ; 
 int DMAE_COMMAND_DST_SHIFT ; 
 int DMAE_COMMAND_DST_VN_SHIFT ; 
 int DMAE_COMMAND_ERR_POLICY_SHIFT ; 
 int DMAE_COMMAND_SRC_SHIFT ; 
 int DMAE_COM_SET_ERR ; 
 int bnx2x_dmae_opcode_add_comp (int,int) ; 

u32 bnx2x_dmae_opcode(struct bnx2x *bp, u8 src_type, u8 dst_type,
			     bool with_comp, u8 comp_type)
{
	u32 opcode = 0;

	opcode |= ((src_type << DMAE_COMMAND_SRC_SHIFT) |
		   (dst_type << DMAE_COMMAND_DST_SHIFT));

	opcode |= (DMAE_CMD_SRC_RESET | DMAE_CMD_DST_RESET);

	opcode |= (BP_PORT(bp) ? DMAE_CMD_PORT_1 : DMAE_CMD_PORT_0);
	opcode |= ((BP_VN(bp) << DMAE_CMD_E1HVN_SHIFT) |
		   (BP_VN(bp) << DMAE_COMMAND_DST_VN_SHIFT));
	opcode |= (DMAE_COM_SET_ERR << DMAE_COMMAND_ERR_POLICY_SHIFT);

#ifdef __BIG_ENDIAN
	opcode |= DMAE_CMD_ENDIANITY_B_DW_SWAP;
#else
	opcode |= DMAE_CMD_ENDIANITY_DW_SWAP;
#endif
	if (with_comp)
		opcode = bnx2x_dmae_opcode_add_comp(opcode, comp_type);
	return opcode;
}