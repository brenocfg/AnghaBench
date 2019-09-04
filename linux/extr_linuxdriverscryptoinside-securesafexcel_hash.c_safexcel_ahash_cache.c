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
typedef  scalar_t__ u64 ;
struct safexcel_ahash_req {scalar_t__ cache; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int E2BIG ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 scalar_t__ crypto_ahash_blocksize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 scalar_t__ safexcel_queued_len (struct safexcel_ahash_req*) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_ahash_cache(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	u64 queued, cache_len;

	/* queued: everything accepted by the driver which will be handled by
	 * the next send() calls.
	 * tot sz handled by update() - tot sz handled by send()
	 */
	queued = safexcel_queued_len(req);
	/* cache_len: everything accepted by the driver but not sent yet,
	 * tot sz handled by update() - last req sz - tot sz handled by send()
	 */
	cache_len = queued - areq->nbytes;

	/*
	 * In case there isn't enough bytes to proceed (less than a
	 * block size), cache the data until we have enough.
	 */
	if (cache_len + areq->nbytes <= crypto_ahash_blocksize(ahash)) {
		sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
				   req->cache + cache_len,
				   areq->nbytes, 0);
		return areq->nbytes;
	}

	/* We couldn't cache all the data */
	return -E2BIG;
}