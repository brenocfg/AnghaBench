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
struct morus640_state {int dummy; } ;
struct morus640_ops {int dummy; } ;
struct morus640_ctx {int /*<<< orphan*/  key; } ;
struct morus640_block {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 struct morus640_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_morus640_final (struct morus640_state*,struct morus640_block*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_morus640_init (struct morus640_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus640_process_ad (struct morus640_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus640_process_crypt (struct morus640_state*,struct aead_request*,struct morus640_ops const*) ; 

__attribute__((used)) static void crypto_morus640_crypt(struct aead_request *req,
				  struct morus640_block *tag_xor,
				  unsigned int cryptlen,
				  const struct morus640_ops *ops)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct morus640_ctx *ctx = crypto_aead_ctx(tfm);
	struct morus640_state state;

	crypto_morus640_init(&state, &ctx->key, req->iv);
	crypto_morus640_process_ad(&state, req->src, req->assoclen);
	crypto_morus640_process_crypt(&state, req, ops);
	crypto_morus640_final(&state, tag_xor, req->assoclen, cryptlen);
}