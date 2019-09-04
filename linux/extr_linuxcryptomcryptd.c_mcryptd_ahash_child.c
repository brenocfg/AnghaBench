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
struct mcryptd_hash_ctx {struct crypto_ahash* child; } ;
struct mcryptd_ahash {int /*<<< orphan*/  base; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 struct mcryptd_hash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ *) ; 

struct crypto_ahash *mcryptd_ahash_child(struct mcryptd_ahash *tfm)
{
	struct mcryptd_hash_ctx *ctx = crypto_ahash_ctx(&tfm->base);

	return ctx->child;
}