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
struct crypto_skcipher {int dummy; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_cfb_ctx {struct crypto_cipher* child; } ;

/* Variables and functions */
 unsigned int crypto_cipher_blocksize (struct crypto_cipher*) ; 
 struct crypto_cfb_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static unsigned int crypto_cfb_bsize(struct crypto_skcipher *tfm)
{
	struct crypto_cfb_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_cipher *child = ctx->child;

	return crypto_cipher_blocksize(child);
}