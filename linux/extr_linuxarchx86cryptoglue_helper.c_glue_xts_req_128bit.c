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
struct skcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; } ;
struct skcipher_request {int dummy; } ;
struct common_glue_ctx {int /*<<< orphan*/  fpu_blocks_limit; } ;
typedef  int /*<<< orphan*/  (* common_glue_func_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 unsigned int __glue_xts_req_128bit (struct common_glue_ctx const*,void*,struct skcipher_walk*) ; 
 int glue_fpu_begin (unsigned int const,int /*<<< orphan*/ ,struct skcipher_walk*,int,unsigned int const) ; 
 int /*<<< orphan*/  glue_fpu_end (int) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

int glue_xts_req_128bit(const struct common_glue_ctx *gctx,
			struct skcipher_request *req,
			common_glue_func_t tweak_fn, void *tweak_ctx,
			void *crypt_ctx)
{
	const unsigned int bsize = 128 / 8;
	struct skcipher_walk walk;
	bool fpu_enabled = false;
	unsigned int nbytes;
	int err;

	err = skcipher_walk_virt(&walk, req, false);
	nbytes = walk.nbytes;
	if (!nbytes)
		return err;

	/* set minimum length to bsize, for tweak_fn */
	fpu_enabled = glue_fpu_begin(bsize, gctx->fpu_blocks_limit,
				     &walk, fpu_enabled,
				     nbytes < bsize ? bsize : nbytes);

	/* calculate first value of T */
	tweak_fn(tweak_ctx, walk.iv, walk.iv);

	while (nbytes) {
		nbytes = __glue_xts_req_128bit(gctx, crypt_ctx, &walk);

		err = skcipher_walk_done(&walk, nbytes);
		nbytes = walk.nbytes;
	}

	glue_fpu_end(fpu_enabled);

	return err;
}