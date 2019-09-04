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
struct safexcel_ahash_req {scalar_t__* len; scalar_t__ digest; int /*<<< orphan*/  last_req; scalar_t__ hmac; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {scalar_t__ nbytes; } ;

/* Variables and functions */
 scalar_t__ CONTEXT_CONTROL_DIGEST_HMAC ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 scalar_t__ crypto_ahash_blocksize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  safexcel_ahash_cache (struct ahash_request*) ; 
 int safexcel_ahash_enqueue (struct ahash_request*) ; 
 scalar_t__ safexcel_queued_len (struct safexcel_ahash_req*) ; 

__attribute__((used)) static int safexcel_ahash_update(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);

	/* If the request is 0 length, do nothing */
	if (!areq->nbytes)
		return 0;

	req->len[0] += areq->nbytes;
	if (req->len[0] < areq->nbytes)
		req->len[1]++;

	safexcel_ahash_cache(areq);

	/*
	 * We're not doing partial updates when performing an hmac request.
	 * Everything will be handled by the final() call.
	 */
	if (req->digest == CONTEXT_CONTROL_DIGEST_HMAC)
		return 0;

	if (req->hmac)
		return safexcel_ahash_enqueue(areq);

	if (!req->last_req &&
	    safexcel_queued_len(req) > crypto_ahash_blocksize(ahash))
		return safexcel_ahash_enqueue(areq);

	return 0;
}