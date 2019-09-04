#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct crypto_ctr_ctx {struct crypto_cipher* child; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_blkcipher {int dummy; } ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 struct crypto_ctr_ctx* crypto_blkcipher_ctx (struct crypto_blkcipher*) ; 
 unsigned int crypto_cipher_blocksize (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_ctr_crypt_final (struct blkcipher_walk*,struct crypto_cipher*) ; 
 unsigned int crypto_ctr_crypt_inplace (struct blkcipher_walk*,struct crypto_cipher*) ; 
 unsigned int crypto_ctr_crypt_segment (struct blkcipher_walk*,struct crypto_cipher*) ; 

__attribute__((used)) static int crypto_ctr_crypt(struct blkcipher_desc *desc,
			      struct scatterlist *dst, struct scatterlist *src,
			      unsigned int nbytes)
{
	struct blkcipher_walk walk;
	struct crypto_blkcipher *tfm = desc->tfm;
	struct crypto_ctr_ctx *ctx = crypto_blkcipher_ctx(tfm);
	struct crypto_cipher *child = ctx->child;
	unsigned int bsize = crypto_cipher_blocksize(child);
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt_block(desc, &walk, bsize);

	while (walk.nbytes >= bsize) {
		if (walk.src.virt.addr == walk.dst.virt.addr)
			nbytes = crypto_ctr_crypt_inplace(&walk, child);
		else
			nbytes = crypto_ctr_crypt_segment(&walk, child);

		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	if (walk.nbytes) {
		crypto_ctr_crypt_final(&walk, child);
		err = blkcipher_walk_done(desc, &walk, 0);
	}

	return err;
}