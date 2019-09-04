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
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addiu ; 
 int /*<<< orphan*/  emit_addu (unsigned int,int /*<<< orphan*/ ,unsigned int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_load_imm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  is_range16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_tmp ; 

__attribute__((used)) static inline void emit_addiu(unsigned int dst, unsigned int src,
			      u32 imm, struct jit_ctx *ctx)
{
	if (!is_range16(imm)) {
		emit_load_imm(r_tmp, imm, ctx);
		emit_addu(dst, r_tmp, src, ctx);
	} else {
		emit_instr(ctx, addiu, dst, src, imm);
	}
}