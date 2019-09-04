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
struct jit_ctx {scalar_t__ cpu_architecture; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FP ; 
 int /*<<< orphan*/  ARM_LDRD_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_LDR_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_ARCH_ARMv5TE ; 
 int /*<<< orphan*/  EBPF_SCRATCH_TO_ARM_FP (int /*<<< orphan*/  const) ; 
 int __LINUX_ARM_ARCH__ ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ is_stacked (int /*<<< orphan*/  const) ; 

__attribute__((used)) static const s8 *arm_bpf_get_reg64(const s8 *reg, const s8 *tmp,
				   struct jit_ctx *ctx)
{
	if (is_stacked(reg[1])) {
		if (__LINUX_ARM_ARCH__ >= 6 ||
		    ctx->cpu_architecture >= CPU_ARCH_ARMv5TE) {
			emit(ARM_LDRD_I(tmp[1], ARM_FP,
					EBPF_SCRATCH_TO_ARM_FP(reg[1])), ctx);
		} else {
			emit(ARM_LDR_I(tmp[1], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[1])), ctx);
			emit(ARM_LDR_I(tmp[0], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[0])), ctx);
		}
		reg = tmp;
	}
	return reg;
}