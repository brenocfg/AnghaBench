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
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_AND_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_EOR_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_LSL_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_LSR_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_MOV_SR (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_MUL (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_ORR_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
#define  BPF_ADD 136 
#define  BPF_AND 135 
#define  BPF_ARSH 134 
#define  BPF_LSH 133 
#define  BPF_MUL 132 
 int BPF_OP (int /*<<< orphan*/  const) ; 
#define  BPF_OR 131 
#define  BPF_RSH 130 
#define  BPF_SUB 129 
#define  BPF_XOR 128 
 int /*<<< orphan*/  SRTYPE_ASR ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_a32_add_r (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int const,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_a32_sub_r (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int const,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_alu_r(const u8 dst, const u8 src, const bool is64,
			      const bool hi, const u8 op, struct jit_ctx *ctx){
	switch (BPF_OP(op)) {
	/* dst = dst + src */
	case BPF_ADD:
		emit_a32_add_r(dst, src, is64, hi, ctx);
		break;
	/* dst = dst - src */
	case BPF_SUB:
		emit_a32_sub_r(dst, src, is64, hi, ctx);
		break;
	/* dst = dst | src */
	case BPF_OR:
		emit(ARM_ORR_R(dst, dst, src), ctx);
		break;
	/* dst = dst & src */
	case BPF_AND:
		emit(ARM_AND_R(dst, dst, src), ctx);
		break;
	/* dst = dst ^ src */
	case BPF_XOR:
		emit(ARM_EOR_R(dst, dst, src), ctx);
		break;
	/* dst = dst * src */
	case BPF_MUL:
		emit(ARM_MUL(dst, dst, src), ctx);
		break;
	/* dst = dst << src */
	case BPF_LSH:
		emit(ARM_LSL_R(dst, dst, src), ctx);
		break;
	/* dst = dst >> src */
	case BPF_RSH:
		emit(ARM_LSR_R(dst, dst, src), ctx);
		break;
	/* dst = dst >> src (signed)*/
	case BPF_ARSH:
		emit(ARM_MOV_SR(dst, dst, SRTYPE_ASR, src), ctx);
		break;
	}
}