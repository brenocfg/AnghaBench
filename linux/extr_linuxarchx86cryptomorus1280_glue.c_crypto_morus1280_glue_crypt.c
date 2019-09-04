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
struct skcipher_walk {int dummy; } ;
struct morus1280_state {int dummy; } ;
struct morus1280_ops {int /*<<< orphan*/  (* skcipher_walk_init ) (struct skcipher_walk*,struct aead_request*,int) ;} ;
struct morus1280_ctx {TYPE_1__* ops; int /*<<< orphan*/  key; } ;
struct morus1280_block {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* final ) (struct morus1280_state*,struct morus1280_block*,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* init ) (struct morus1280_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct morus1280_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_morus1280_glue_process_ad (struct morus1280_state*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus1280_glue_process_crypt (struct morus1280_state*,struct morus1280_ops,struct skcipher_walk*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int /*<<< orphan*/  stub1 (struct skcipher_walk*,struct aead_request*,int) ; 
 int /*<<< orphan*/  stub2 (struct morus1280_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct morus1280_state*,struct morus1280_block*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void crypto_morus1280_glue_crypt(struct aead_request *req,
					struct morus1280_ops ops,
					unsigned int cryptlen,
					struct morus1280_block *tag_xor)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct morus1280_ctx *ctx = crypto_aead_ctx(tfm);
	struct morus1280_state state;
	struct skcipher_walk walk;

	ops.skcipher_walk_init(&walk, req, true);

	kernel_fpu_begin();

	ctx->ops->init(&state, &ctx->key, req->iv);
	crypto_morus1280_glue_process_ad(&state, ctx->ops, req->src, req->assoclen);
	crypto_morus1280_glue_process_crypt(&state, ops, &walk);
	ctx->ops->final(&state, tag_xor, req->assoclen, cryptlen);

	kernel_fpu_end();
}