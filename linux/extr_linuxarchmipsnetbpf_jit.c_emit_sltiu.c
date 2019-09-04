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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  emit_load_imm (int /*<<< orphan*/ ,unsigned int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_sltu (unsigned int,unsigned int,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  is_range16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_tmp ; 
 int /*<<< orphan*/  sltiu ; 

__attribute__((used)) static inline void emit_sltiu(unsigned dst, unsigned int src,
			      unsigned int imm, struct jit_ctx *ctx)
{
	/* 16 bit immediate */
	if (!is_range16((s32)imm)) {
		emit_load_imm(r_tmp, imm, ctx);
		emit_sltu(dst, src, r_tmp, ctx);
	} else {
		emit_instr(ctx, sltiu, dst, src, imm);
	}

}