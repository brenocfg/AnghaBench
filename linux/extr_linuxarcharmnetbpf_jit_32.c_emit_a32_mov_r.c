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
 size_t TMP_REG_1 ; 
 int /*<<< orphan*/  arm_bpf_get_reg32 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/  arm_bpf_put_reg32 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/ ** bpf2a32 ; 

__attribute__((used)) static inline void emit_a32_mov_r(const s8 dst, const s8 src,
				  struct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_REG_1];
	s8 rt;

	rt = arm_bpf_get_reg32(src, tmp[0], ctx);
	arm_bpf_put_reg32(dst, rt, ctx);
}