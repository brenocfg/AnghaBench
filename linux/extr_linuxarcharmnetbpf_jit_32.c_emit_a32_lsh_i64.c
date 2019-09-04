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
typedef  int u32 ;
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_EOR_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_MOV_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_MOV_SI (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ARM_ORR_SI (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRTYPE_ASL ; 
 int /*<<< orphan*/  SRTYPE_LSR ; 
 size_t TMP_REG_1 ; 
 size_t TMP_REG_2 ; 
 int /*<<< orphan*/ * arm_bpf_get_reg64 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct jit_ctx*) ; 
 int /*<<< orphan*/  arm_bpf_put_reg64 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct jit_ctx*) ; 
 int /*<<< orphan*/ ** bpf2a32 ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_a32_lsh_i64(const s8 dst[],
				    const u32 val, struct jit_ctx *ctx){
	const s8 *tmp = bpf2a32[TMP_REG_1];
	const s8 *tmp2 = bpf2a32[TMP_REG_2];
	const s8 *rd;

	/* Setup operands */
	rd = arm_bpf_get_reg64(dst, tmp, ctx);

	/* Do LSH operation */
	if (val < 32) {
		emit(ARM_MOV_SI(tmp2[0], rd[0], SRTYPE_ASL, val), ctx);
		emit(ARM_ORR_SI(rd[0], tmp2[0], rd[1], SRTYPE_LSR, 32 - val), ctx);
		emit(ARM_MOV_SI(rd[1], rd[1], SRTYPE_ASL, val), ctx);
	} else {
		if (val == 32)
			emit(ARM_MOV_R(rd[0], rd[1]), ctx);
		else
			emit(ARM_MOV_SI(rd[0], rd[1], SRTYPE_ASL, val - 32), ctx);
		emit(ARM_EOR_R(rd[1], rd[1], rd[1]), ctx);
	}

	arm_bpf_put_reg64(dst, rd, ctx);
}