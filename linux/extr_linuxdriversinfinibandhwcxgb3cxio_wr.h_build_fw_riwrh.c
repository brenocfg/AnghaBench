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
struct TYPE_2__ {int /*<<< orphan*/  genbit; } ;
union t3_wr {TYPE_1__ genbit; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fw_riwrh {void* gen_tid_len; void* op_seop_flags; } ;
typedef  enum t3_wr_opcode { ____Placeholder_t3_wr_opcode } t3_wr_opcode ;
typedef  enum t3_wr_flags { ____Placeholder_t3_wr_flags } t3_wr_flags ;

/* Variables and functions */
 int V_FW_RIWR_FLAGS (int) ; 
 int V_FW_RIWR_GEN (int /*<<< orphan*/ ) ; 
 int V_FW_RIWR_LEN (int /*<<< orphan*/ ) ; 
 int V_FW_RIWR_OP (int) ; 
 int V_FW_RIWR_SOPEOP (int /*<<< orphan*/ ) ; 
 int V_FW_RIWR_TID (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void build_fw_riwrh(struct fw_riwrh *wqe, enum t3_wr_opcode op,
				  enum t3_wr_flags flags, u8 genbit, u32 tid,
				  u8 len, u8 sopeop)
{
	wqe->op_seop_flags = cpu_to_be32(V_FW_RIWR_OP(op) |
					 V_FW_RIWR_SOPEOP(sopeop) |
					 V_FW_RIWR_FLAGS(flags));
	wmb();
	wqe->gen_tid_len = cpu_to_be32(V_FW_RIWR_GEN(genbit) |
				       V_FW_RIWR_TID(tid) |
				       V_FW_RIWR_LEN(len));
	/* 2nd gen bit... */
	((union t3_wr *)wqe)->genbit.genbit = cpu_to_be64(genbit);
}