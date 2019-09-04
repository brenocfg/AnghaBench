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
typedef  int /*<<< orphan*/  u64 ;
struct mv_cesa_ahash_req {unsigned int cache_ptr; int /*<<< orphan*/  cache; int /*<<< orphan*/  state; int /*<<< orphan*/  len; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 unsigned int crypto_ahash_blocksize (struct crypto_ahash*) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mv_cesa_ahash_export(struct ahash_request *req, void *hash,
				u64 *len, void *cache)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	unsigned int digsize = crypto_ahash_digestsize(ahash);
	unsigned int blocksize;

	blocksize = crypto_ahash_blocksize(ahash);

	*len = creq->len;
	memcpy(hash, creq->state, digsize);
	memset(cache, 0, blocksize);
	memcpy(cache, creq->cache, creq->cache_ptr);

	return 0;
}