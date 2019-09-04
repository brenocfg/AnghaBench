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
struct TYPE_3__ {int /*<<< orphan*/ * tfms; } ;
struct crypt_config {int tfms_count; TYPE_1__ cipher_tfm; int /*<<< orphan*/  req_pool; } ;
struct TYPE_4__ {scalar_t__ req; } ;
struct convert_context {int cc_sector; TYPE_2__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  dmreq_of_req (struct crypt_config*,scalar_t__) ; 
 int /*<<< orphan*/  kcryptd_async_done ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypt_alloc_req_skcipher(struct crypt_config *cc,
				     struct convert_context *ctx)
{
	unsigned key_index = ctx->cc_sector & (cc->tfms_count - 1);

	if (!ctx->r.req)
		ctx->r.req = mempool_alloc(&cc->req_pool, GFP_NOIO);

	skcipher_request_set_tfm(ctx->r.req, cc->cipher_tfm.tfms[key_index]);

	/*
	 * Use REQ_MAY_BACKLOG so a cipher driver internally backlogs
	 * requests if driver request queue is full.
	 */
	skcipher_request_set_callback(ctx->r.req,
	    CRYPTO_TFM_REQ_MAY_BACKLOG,
	    kcryptd_async_done, dmreq_of_req(cc, ctx->r.req));
}