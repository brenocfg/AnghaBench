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
struct mcryptd_queue {int dummy; } ;
struct mcryptd_hash_request_ctx {int /*<<< orphan*/  complete; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct ahash_request {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 struct mcryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 int mcryptd_enqueue_request (struct mcryptd_queue*,TYPE_1__*,struct mcryptd_hash_request_ctx*) ; 
 struct mcryptd_queue* mcryptd_get_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcryptd_hash_enqueue(struct ahash_request *req,
				crypto_completion_t complete)
{
	int ret;

	struct mcryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct mcryptd_queue *queue =
		mcryptd_get_queue(crypto_ahash_tfm(tfm));

	rctx->complete = req->base.complete;
	req->base.complete = complete;

	ret = mcryptd_enqueue_request(queue, &req->base, rctx);

	return ret;
}