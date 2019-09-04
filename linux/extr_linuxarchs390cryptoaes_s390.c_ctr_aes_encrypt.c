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
struct scatterlist {int dummy; } ;
struct s390_aes_ctx {int /*<<< orphan*/  fc; } ;
struct blkcipher_walk {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 struct s390_aes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int ctr_aes_crypt (struct blkcipher_desc*,int /*<<< orphan*/ ,struct blkcipher_walk*) ; 
 int fallback_blk_enc (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ctr_aes_encrypt(struct blkcipher_desc *desc,
			   struct scatterlist *dst, struct scatterlist *src,
			   unsigned int nbytes)
{
	struct s390_aes_ctx *sctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;

	if (unlikely(!sctx->fc))
		return fallback_blk_enc(desc, dst, src, nbytes);

	blkcipher_walk_init(&walk, dst, src, nbytes);
	return ctr_aes_crypt(desc, 0, &walk);
}