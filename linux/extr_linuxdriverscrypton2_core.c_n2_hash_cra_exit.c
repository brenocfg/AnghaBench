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
struct n2_hash_ctx {int /*<<< orphan*/  fallback_tfm; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 struct crypto_ahash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 struct n2_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_free_ahash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n2_hash_cra_exit(struct crypto_tfm *tfm)
{
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	struct n2_hash_ctx *ctx = crypto_ahash_ctx(ahash);

	crypto_free_ahash(ctx->fallback_tfm);
}