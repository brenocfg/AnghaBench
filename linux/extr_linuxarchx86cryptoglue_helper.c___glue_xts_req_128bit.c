#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u128 ;
struct TYPE_9__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {TYPE_3__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct common_glue_ctx {unsigned int num_funcs; TYPE_6__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* xts ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {unsigned int num_blocks; TYPE_5__ fn_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __glue_xts_req_128bit(const struct common_glue_ctx *gctx,
					  void *ctx,
					  struct skcipher_walk *walk)
{
	const unsigned int bsize = 128 / 8;
	unsigned int nbytes = walk->nbytes;
	u128 *src = walk->src.virt.addr;
	u128 *dst = walk->dst.virt.addr;
	unsigned int num_blocks, func_bytes;
	unsigned int i;

	/* Process multi-block batch */
	for (i = 0; i < gctx->num_funcs; i++) {
		num_blocks = gctx->funcs[i].num_blocks;
		func_bytes = bsize * num_blocks;

		if (nbytes >= func_bytes) {
			do {
				gctx->funcs[i].fn_u.xts(ctx, dst, src,
							walk->iv);

				src += num_blocks;
				dst += num_blocks;
				nbytes -= func_bytes;
			} while (nbytes >= func_bytes);

			if (nbytes < bsize)
				goto done;
		}
	}

done:
	return nbytes;
}