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
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  const ARM_IP ; 
 int /*<<< orphan*/  const ARM_LR ; 
 int /*<<< orphan*/  ARM_MOV_SR (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_ORR_SR (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_RSB_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARM_SUB_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRTYPE_ASL ; 
 int /*<<< orphan*/  SRTYPE_LSR ; 
 size_t TMP_REG_1 ; 
 size_t TMP_REG_2 ; 
 int /*<<< orphan*/  arm_bpf_get_reg32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/ * arm_bpf_get_reg64 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct jit_ctx*) ; 
 int /*<<< orphan*/  arm_bpf_put_reg32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/ ** bpf2a32 ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  src_lo ; 

__attribute__((used)) static inline void emit_a32_lsh_r64(const s8 dst[], const s8 src[],
				    struct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_REG_1];
	const s8 *tmp2 = bpf2a32[TMP_REG_2];
	const s8 *rd;
	s8 rt;

	/* Setup Operands */
	rt = arm_bpf_get_reg32(src_lo, tmp2[1], ctx);
	rd = arm_bpf_get_reg64(dst, tmp, ctx);

	/* Do LSH operation */
	emit(ARM_SUB_I(ARM_IP, rt, 32), ctx);
	emit(ARM_RSB_I(tmp2[0], rt, 32), ctx);
	emit(ARM_MOV_SR(ARM_LR, rd[0], SRTYPE_ASL, rt), ctx);
	emit(ARM_ORR_SR(ARM_LR, ARM_LR, rd[1], SRTYPE_ASL, ARM_IP), ctx);
	emit(ARM_ORR_SR(ARM_IP, ARM_LR, rd[1], SRTYPE_LSR, tmp2[0]), ctx);
	emit(ARM_MOV_SR(ARM_LR, rd[1], SRTYPE_ASL, rt), ctx);

	arm_bpf_put_reg32(dst_lo, ARM_LR, ctx);
	arm_bpf_put_reg32(dst_hi, ARM_IP, ctx);
}