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
typedef  int u64 ;
struct scatterlist {int dummy; } ;
struct scatter_walk {int dummy; } ;
struct crypto_kw_ctx {struct crypto_cipher* child; } ;
struct crypto_kw_block {int /*<<< orphan*/  A; int /*<<< orphan*/  R; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_blkcipher {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  info; struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 int EINVAL ; 
 int SEMIBSIZE ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 struct crypto_kw_ctx* crypto_blkcipher_ctx (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_kw_block*,int) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ *,struct scatter_walk*,int,int) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 

__attribute__((used)) static int crypto_kw_encrypt(struct blkcipher_desc *desc,
			     struct scatterlist *dst, struct scatterlist *src,
			     unsigned int nbytes)
{
	struct crypto_blkcipher *tfm = desc->tfm;
	struct crypto_kw_ctx *ctx = crypto_blkcipher_ctx(tfm);
	struct crypto_cipher *child = ctx->child;
	struct crypto_kw_block block;
	struct scatterlist *lsrc, *ldst;
	u64 t = 1;
	unsigned int i;

	/*
	 * Require at least 2 semiblocks (note, the 3rd semiblock that is
	 * required by SP800-38F is the IV that occupies the first semiblock.
	 * This means that the dst memory must be one semiblock larger than src.
	 * Also ensure that the given data is aligned to semiblock.
	 */
	if (nbytes < (2 * SEMIBSIZE) || nbytes % SEMIBSIZE)
		return -EINVAL;

	/*
	 * Place the predefined IV into block A -- for encrypt, the caller
	 * does not need to provide an IV, but he needs to fetch the final IV.
	 */
	block.A = cpu_to_be64(0xa6a6a6a6a6a6a6a6ULL);

	/*
	 * src scatterlist is read-only. dst scatterlist is r/w. During the
	 * first loop, lsrc points to src and ldst to dst. For any
	 * subsequent round, the code operates on dst only.
	 */
	lsrc = src;
	ldst = dst;

	for (i = 0; i < 6; i++) {
		struct scatter_walk src_walk, dst_walk;
		unsigned int tmp_nbytes = nbytes;

		scatterwalk_start(&src_walk, lsrc);
		scatterwalk_start(&dst_walk, ldst);

		while (tmp_nbytes) {
			/* get the source block */
			scatterwalk_copychunks(&block.R, &src_walk, SEMIBSIZE,
					       false);

			/* perform KW operation: encrypt block */
			crypto_cipher_encrypt_one(child, (u8 *)&block,
						  (u8 *)&block);
			/* perform KW operation: modify IV with counter */
			block.A ^= cpu_to_be64(t);
			t++;

			/* Copy block->R into place */
			scatterwalk_copychunks(&block.R, &dst_walk, SEMIBSIZE,
					       true);

			tmp_nbytes -= SEMIBSIZE;
		}

		/* we now start to operate on the dst SGL only */
		lsrc = dst;
		ldst = dst;
	}

	/* establish the IV for the caller to pick up */
	memcpy(desc->info, &block.A, SEMIBSIZE);

	memzero_explicit(&block, sizeof(struct crypto_kw_block));

	return 0;
}