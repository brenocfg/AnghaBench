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
struct crypto_ecb_ctx {struct crypto_cipher* child; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_blkcipher {int dummy; } ;
struct blkcipher_walk {int dummy; } ;
struct blkcipher_desc {struct crypto_blkcipher* tfm; } ;
struct TYPE_2__ {int /*<<< orphan*/  cia_encrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 struct crypto_ecb_ctx* crypto_blkcipher_ctx (struct crypto_blkcipher*) ; 
 TYPE_1__* crypto_cipher_alg (struct crypto_cipher*) ; 
 int crypto_ecb_crypt (struct blkcipher_desc*,struct blkcipher_walk*,struct crypto_cipher*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_ecb_encrypt(struct blkcipher_desc *desc,
			      struct scatterlist *dst, struct scatterlist *src,
			      unsigned int nbytes)
{
	struct blkcipher_walk walk;
	struct crypto_blkcipher *tfm = desc->tfm;
	struct crypto_ecb_ctx *ctx = crypto_blkcipher_ctx(tfm);
	struct crypto_cipher *child = ctx->child;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	return crypto_ecb_crypt(desc, &walk, child,
				crypto_cipher_alg(child)->cia_encrypt);
}