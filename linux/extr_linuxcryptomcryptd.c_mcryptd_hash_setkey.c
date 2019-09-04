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
struct mcryptd_hash_ctx {struct crypto_ahash* child; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_ahash_clear_flags (struct crypto_ahash*,int) ; 
 struct mcryptd_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_get_flags (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int) ; 
 int crypto_ahash_setkey (struct crypto_ahash*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int mcryptd_hash_setkey(struct crypto_ahash *parent,
				   const u8 *key, unsigned int keylen)
{
	struct mcryptd_hash_ctx *ctx   = crypto_ahash_ctx(parent);
	struct crypto_ahash *child = ctx->child;
	int err;

	crypto_ahash_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(child, crypto_ahash_get_flags(parent) &
				      CRYPTO_TFM_REQ_MASK);
	err = crypto_ahash_setkey(child, key, keylen);
	crypto_ahash_set_flags(parent, crypto_ahash_get_flags(child) &
				       CRYPTO_TFM_RES_MASK);
	return err;
}