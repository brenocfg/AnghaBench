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
struct jit_ctx {int* target; size_t idx; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  is_range16 (int) ; 
 int /*<<< orphan*/  r_tmp_imm ; 
 int /*<<< orphan*/  r_zero ; 
 int /*<<< orphan*/  uasm_i_addiu (int**,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_i_lui (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_i_ori (int**,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void emit_load_imm(unsigned int dst, u32 imm, struct jit_ctx *ctx)
{
	if (ctx->target != NULL) {
		/* addiu can only handle s16 */
		if (!is_range16(imm)) {
			u32 *p = &ctx->target[ctx->idx];
			uasm_i_lui(&p, r_tmp_imm, (s32)imm >> 16);
			p = &ctx->target[ctx->idx + 1];
			uasm_i_ori(&p, dst, r_tmp_imm, imm & 0xffff);
		} else {
			u32 *p = &ctx->target[ctx->idx];
			uasm_i_addiu(&p, dst, r_zero, imm);
		}
	}
	ctx->idx++;

	if (!is_range16(imm))
		ctx->idx++;
}