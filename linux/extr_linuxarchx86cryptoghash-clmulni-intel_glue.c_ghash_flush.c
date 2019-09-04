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
struct ghash_desc_ctx {int bytes; int /*<<< orphan*/ * buffer; } ;
struct ghash_ctx {int /*<<< orphan*/  shash; } ;

/* Variables and functions */
 int GHASH_BLOCK_SIZE ; 
 int /*<<< orphan*/  clmul_ghash_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

__attribute__((used)) static void ghash_flush(struct ghash_ctx *ctx, struct ghash_desc_ctx *dctx)
{
	u8 *dst = dctx->buffer;

	if (dctx->bytes) {
		u8 *tmp = dst + (GHASH_BLOCK_SIZE - dctx->bytes);

		while (dctx->bytes--)
			*tmp++ ^= 0;

		kernel_fpu_begin();
		clmul_ghash_mul(dst, &ctx->shash);
		kernel_fpu_end();
	}

	dctx->bytes = 0;
}