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
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_LSL_I (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_LSR_I (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_RSB_I (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
#define  BPF_LSH 130 
#define  BPF_NEG 129 
#define  BPF_RSH 128 
 size_t TMP_REG_1 ; 
 int /*<<< orphan*/  arm_bpf_get_reg32 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/  arm_bpf_put_reg32 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/ ** bpf2a32 ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_a32_alu_i(const s8 dst, const u32 val,
				struct jit_ctx *ctx, const u8 op) {
	const s8 *tmp = bpf2a32[TMP_REG_1];
	s8 rd;

	rd = arm_bpf_get_reg32(dst, tmp[0], ctx);

	/* Do shift operation */
	switch (op) {
	case BPF_LSH:
		emit(ARM_LSL_I(rd, rd, val), ctx);
		break;
	case BPF_RSH:
		emit(ARM_LSR_I(rd, rd, val), ctx);
		break;
	case BPF_NEG:
		emit(ARM_RSB_I(rd, rd, val), ctx);
		break;
	}

	arm_bpf_put_reg32(dst, rd, ctx);
}