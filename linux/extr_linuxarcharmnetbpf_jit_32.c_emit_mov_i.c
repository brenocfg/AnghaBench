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
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_MOV_I (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_mov_i_no8m (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int imm8m (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void emit_mov_i(const u8 rd, u32 val, struct jit_ctx *ctx)
{
	int imm12 = imm8m(val);

	if (imm12 >= 0)
		emit(ARM_MOV_I(rd, imm12), ctx);
	else
		emit_mov_i_no8m(rd, val, ctx);
}