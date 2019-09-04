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
struct TYPE_4__ {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  assoclen; } ;
struct poly_req {int /*<<< orphan*/  req; int /*<<< orphan*/  src; TYPE_2__ tail; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_3__ {struct poly_req poly; } ;
struct chachapoly_req_ctx {int /*<<< orphan*/  tag; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  assoclen; TYPE_1__ u; } ;
struct chachapoly_ctx {int /*<<< orphan*/  poly; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct chachapoly_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ahash_finup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int poly_tail_continue (struct aead_request*) ; 
 int /*<<< orphan*/  poly_tail_done ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static int poly_tail(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chachapoly_ctx *ctx = crypto_aead_ctx(tfm);
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);
	struct poly_req *preq = &rctx->u.poly;
	__le64 len;
	int err;

	sg_init_table(preq->src, 1);
	len = cpu_to_le64(rctx->assoclen);
	memcpy(&preq->tail.assoclen, &len, sizeof(len));
	len = cpu_to_le64(rctx->cryptlen);
	memcpy(&preq->tail.cryptlen, &len, sizeof(len));
	sg_set_buf(preq->src, &preq->tail, sizeof(preq->tail));

	ahash_request_set_callback(&preq->req, aead_request_flags(req),
				   poly_tail_done, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, preq->src,
				rctx->tag, sizeof(preq->tail));

	err = crypto_ahash_finup(&preq->req);
	if (err)
		return err;

	return poly_tail_continue(req);
}