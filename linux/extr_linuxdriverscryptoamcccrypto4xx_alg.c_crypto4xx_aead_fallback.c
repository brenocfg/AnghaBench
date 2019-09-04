#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  aead; } ;
struct crypto4xx_ctx {TYPE_1__ sw_cipher; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_2__ base; } ;

/* Variables and functions */
 struct aead_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 

__attribute__((used)) static int crypto4xx_aead_fallback(struct aead_request *req,
	struct crypto4xx_ctx *ctx, bool do_decrypt)
{
	struct aead_request *subreq = aead_request_ctx(req);

	aead_request_set_tfm(subreq, ctx->sw_cipher.aead);
	aead_request_set_callback(subreq, req->base.flags,
				  req->base.complete, req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
			       req->iv);
	aead_request_set_ad(subreq, req->assoclen);
	return do_decrypt ? crypto_aead_decrypt(subreq) :
			    crypto_aead_encrypt(subreq);
}