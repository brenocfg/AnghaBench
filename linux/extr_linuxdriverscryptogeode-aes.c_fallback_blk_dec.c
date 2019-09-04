#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct TYPE_2__ {struct crypto_blkcipher* blk; } ;
struct geode_aes_op {TYPE_1__ fallback; } ;
struct crypto_blkcipher {int dummy; } ;
struct blkcipher_desc {struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 struct geode_aes_op* crypto_blkcipher_ctx (struct crypto_blkcipher*) ; 
 unsigned int crypto_blkcipher_decrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int fallback_blk_dec(struct blkcipher_desc *desc,
		struct scatterlist *dst, struct scatterlist *src,
		unsigned int nbytes)
{
	unsigned int ret;
	struct crypto_blkcipher *tfm;
	struct geode_aes_op *op = crypto_blkcipher_ctx(desc->tfm);

	tfm = desc->tfm;
	desc->tfm = op->fallback.blk;

	ret = crypto_blkcipher_decrypt_iv(desc, dst, src, nbytes);

	desc->tfm = tfm;
	return ret;
}