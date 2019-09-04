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
struct safexcel_ahash_req {int /*<<< orphan*/  cache; int /*<<< orphan*/  state_sz; int /*<<< orphan*/  state; int /*<<< orphan*/  digest; int /*<<< orphan*/ * processed; int /*<<< orphan*/ * len; } ;
struct safexcel_ahash_export_state {int /*<<< orphan*/  cache; int /*<<< orphan*/  state; int /*<<< orphan*/  digest; int /*<<< orphan*/ * processed; int /*<<< orphan*/ * len; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_blocksize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_ahash_export(struct ahash_request *areq, void *out)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_export_state *export = out;

	export->len[0] = req->len[0];
	export->len[1] = req->len[1];
	export->processed[0] = req->processed[0];
	export->processed[1] = req->processed[1];

	export->digest = req->digest;

	memcpy(export->state, req->state, req->state_sz);
	memcpy(export->cache, req->cache, crypto_ahash_blocksize(ahash));

	return 0;
}