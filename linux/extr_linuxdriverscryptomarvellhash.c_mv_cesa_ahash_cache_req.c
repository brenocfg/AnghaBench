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
struct mv_cesa_ahash_req {scalar_t__ cache_ptr; scalar_t__ cache; int /*<<< orphan*/  src_nents; int /*<<< orphan*/  last_req; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ CESA_MAX_HASH_BLOCK_SIZE ; 
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mv_cesa_ahash_cache_req(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	bool cached = false;

	if (creq->cache_ptr + req->nbytes < CESA_MAX_HASH_BLOCK_SIZE && !creq->last_req) {
		cached = true;

		if (!req->nbytes)
			return cached;

		sg_pcopy_to_buffer(req->src, creq->src_nents,
				   creq->cache + creq->cache_ptr,
				   req->nbytes, 0);

		creq->cache_ptr += req->nbytes;
	}

	return cached;
}