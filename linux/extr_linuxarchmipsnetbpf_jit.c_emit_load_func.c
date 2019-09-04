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
typedef  int u64 ;
struct jit_ctx {int dummy; } ;
typedef  int ptr ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_64BIT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_dsll (int /*<<< orphan*/ ,unsigned int,int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_load_imm (unsigned int,int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_ori (unsigned int,int /*<<< orphan*/ ,int,struct jit_ctx*) ; 
 unsigned int r_tmp ; 
 int /*<<< orphan*/  r_tmp_imm ; 

__attribute__((used)) static inline void emit_load_func(unsigned int reg, ptr imm,
				  struct jit_ctx *ctx)
{
	if (IS_ENABLED(CONFIG_64BIT)) {
		/* At this point imm is always 64-bit */
		emit_load_imm(r_tmp, (u64)imm >> 32, ctx);
		emit_dsll(r_tmp_imm, r_tmp, 16, ctx); /* left shift by 16 */
		emit_ori(r_tmp, r_tmp_imm, (imm >> 16) & 0xffff, ctx);
		emit_dsll(r_tmp_imm, r_tmp, 16, ctx); /* left shift by 16 */
		emit_ori(reg, r_tmp_imm, imm & 0xffff, ctx);
	} else {
		emit_load_imm(reg, imm, ctx);
	}
}