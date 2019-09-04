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
struct safexcel_ahash_req {int /*<<< orphan*/  digest; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_HMAC ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  safexcel_sha384_init (struct ahash_request*) ; 

__attribute__((used)) static int safexcel_hmac_sha384_init(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	safexcel_sha384_init(areq);
	req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	return 0;
}