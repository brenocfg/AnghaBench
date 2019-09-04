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
struct crypto_rfc4106_req_ctx {int dummy; } ;
struct crypto_rfc4106_ctx {struct crypto_aead* child; } ;
struct crypto_aead_spawn {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 struct aead_instance* aead_alg_instance (struct crypto_aead*) ; 
 struct crypto_aead_spawn* aead_instance_ctx (struct aead_instance*) ; 
 unsigned long crypto_aead_alignmask (struct crypto_aead*) ; 
 struct crypto_rfc4106_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_reqsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,scalar_t__) ; 
 struct crypto_aead* crypto_spawn_aead (struct crypto_aead_spawn*) ; 
 int crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static int crypto_rfc4106_init_tfm(struct crypto_aead *tfm)
{
	struct aead_instance *inst = aead_alg_instance(tfm);
	struct crypto_aead_spawn *spawn = aead_instance_ctx(inst);
	struct crypto_rfc4106_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_aead *aead;
	unsigned long align;

	aead = crypto_spawn_aead(spawn);
	if (IS_ERR(aead))
		return PTR_ERR(aead);

	ctx->child = aead;

	align = crypto_aead_alignmask(aead);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		sizeof(struct crypto_rfc4106_req_ctx) +
		ALIGN(crypto_aead_reqsize(aead), crypto_tfm_ctx_alignment()) +
		align + 24);

	return 0;
}