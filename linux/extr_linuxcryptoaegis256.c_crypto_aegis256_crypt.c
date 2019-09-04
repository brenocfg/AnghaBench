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
typedef  union aegis_block {int dummy; } aegis_block ;
struct crypto_aead {int dummy; } ;
struct aegis_state {int dummy; } ;
struct aegis_ctx {int /*<<< orphan*/  key; } ;
struct aegis256_ops {int dummy; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 struct aegis_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_aegis256_final (struct aegis_state*,union aegis_block*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_aegis256_init (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aegis256_process_ad (struct aegis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aegis256_process_crypt (struct aegis_state*,struct aead_request*,struct aegis256_ops const*) ; 

__attribute__((used)) static void crypto_aegis256_crypt(struct aead_request *req,
				  union aegis_block *tag_xor,
				  unsigned int cryptlen,
				  const struct aegis256_ops *ops)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct aegis_ctx *ctx = crypto_aead_ctx(tfm);
	struct aegis_state state;

	crypto_aegis256_init(&state, ctx->key, req->iv);
	crypto_aegis256_process_ad(&state, req->src, req->assoclen);
	crypto_aegis256_process_crypt(&state, req, ops);
	crypto_aegis256_final(&state, tag_xor, req->assoclen, cryptlen);
}