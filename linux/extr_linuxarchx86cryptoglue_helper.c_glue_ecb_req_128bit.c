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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {TYPE_3__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; TYPE_4__ dst; TYPE_2__ src; } ;
struct skcipher_request {int dummy; } ;
struct common_glue_ctx {unsigned int num_funcs; TYPE_6__* funcs; int /*<<< orphan*/  fpu_blocks_limit; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* ecb ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
struct TYPE_12__ {unsigned int const num_blocks; TYPE_5__ fn_u; } ;

/* Variables and functions */
 void* crypto_skcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int glue_fpu_begin (unsigned int const,int /*<<< orphan*/ ,struct skcipher_walk*,int,unsigned int) ; 
 int /*<<< orphan*/  glue_fpu_end (int) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int glue_ecb_req_128bit(const struct common_glue_ctx *gctx,
			struct skcipher_request *req)
{
	void *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	const unsigned int bsize = 128 / 8;
	struct skcipher_walk walk;
	bool fpu_enabled = false;
	unsigned int nbytes;
	int err;

	err = skcipher_walk_virt(&walk, req, false);

	while ((nbytes = walk.nbytes)) {
		const u8 *src = walk.src.virt.addr;
		u8 *dst = walk.dst.virt.addr;
		unsigned int func_bytes;
		unsigned int i;

		fpu_enabled = glue_fpu_begin(bsize, gctx->fpu_blocks_limit,
					     &walk, fpu_enabled, nbytes);
		for (i = 0; i < gctx->num_funcs; i++) {
			func_bytes = bsize * gctx->funcs[i].num_blocks;

			if (nbytes < func_bytes)
				continue;

			/* Process multi-block batch */
			do {
				gctx->funcs[i].fn_u.ecb(ctx, dst, src);
				src += func_bytes;
				dst += func_bytes;
				nbytes -= func_bytes;
			} while (nbytes >= func_bytes);

			if (nbytes < bsize)
				break;
		}
		err = skcipher_walk_done(&walk, nbytes);
	}

	glue_fpu_end(fpu_enabled);
	return err;
}