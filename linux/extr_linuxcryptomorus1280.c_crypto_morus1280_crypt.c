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
struct morus1280_state {int dummy; } ;
struct morus1280_ops {int dummy; } ;
struct morus1280_ctx {int /*<<< orphan*/  key; } ;
struct morus1280_block {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 struct morus1280_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_morus1280_final (struct morus1280_state*,struct morus1280_block*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_morus1280_init (struct morus1280_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus1280_process_ad (struct morus1280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus1280_process_crypt (struct morus1280_state*,struct aead_request*,struct morus1280_ops const*) ; 

__attribute__((used)) static void crypto_morus1280_crypt(struct aead_request *req,
				   struct morus1280_block *tag_xor,
				   unsigned int cryptlen,
				   const struct morus1280_ops *ops)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct morus1280_ctx *ctx = crypto_aead_ctx(tfm);
	struct morus1280_state state;

	crypto_morus1280_init(&state, &ctx->key, req->iv);
	crypto_morus1280_process_ad(&state, req->src, req->assoclen);
	crypto_morus1280_process_crypt(&state, req, ops);
	crypto_morus1280_final(&state, tag_xor, req->assoclen, cryptlen);
}