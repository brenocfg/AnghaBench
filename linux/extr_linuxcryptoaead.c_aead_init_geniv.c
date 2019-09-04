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
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;
struct aead_instance {int dummy; } ;
struct aead_geniv_ctx {struct crypto_aead* child; struct crypto_aead* sknull; int /*<<< orphan*/  salt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 struct aead_instance* aead_alg_instance (struct crypto_aead*) ; 
 int /*<<< orphan*/  aead_instance_ctx (struct aead_instance*) ; 
 struct aead_geniv_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_ivsize (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_reqsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,scalar_t__) ; 
 int /*<<< orphan*/  crypto_default_rng ; 
 struct crypto_aead* crypto_get_default_null_skcipher () ; 
 int crypto_get_default_rng () ; 
 int /*<<< orphan*/  crypto_put_default_null_skcipher () ; 
 int /*<<< orphan*/  crypto_put_default_rng () ; 
 int crypto_rng_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_aead* crypto_spawn_aead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int aead_init_geniv(struct crypto_aead *aead)
{
	struct aead_geniv_ctx *ctx = crypto_aead_ctx(aead);
	struct aead_instance *inst = aead_alg_instance(aead);
	struct crypto_aead *child;
	int err;

	spin_lock_init(&ctx->lock);

	err = crypto_get_default_rng();
	if (err)
		goto out;

	err = crypto_rng_get_bytes(crypto_default_rng, ctx->salt,
				   crypto_aead_ivsize(aead));
	crypto_put_default_rng();
	if (err)
		goto out;

	ctx->sknull = crypto_get_default_null_skcipher();
	err = PTR_ERR(ctx->sknull);
	if (IS_ERR(ctx->sknull))
		goto out;

	child = crypto_spawn_aead(aead_instance_ctx(inst));
	err = PTR_ERR(child);
	if (IS_ERR(child))
		goto drop_null;

	ctx->child = child;
	crypto_aead_set_reqsize(aead, crypto_aead_reqsize(child) +
				      sizeof(struct aead_request));

	err = 0;

out:
	return err;

drop_null:
	crypto_put_default_null_skcipher();
	goto out;
}