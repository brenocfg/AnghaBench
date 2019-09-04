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
struct jit_ctx {unsigned int* image; size_t idx; } ;

/* Variables and functions */
 unsigned int CALL ; 

__attribute__((used)) static void emit_call(u32 *func, struct jit_ctx *ctx)
{
	if (ctx->image != NULL) {
		void *here = &ctx->image[ctx->idx];
		unsigned int off;

		off = (void *)func - here;
		ctx->image[ctx->idx] = CALL | ((off >> 2) & 0x3fffffff);
	}
	ctx->idx++;
}