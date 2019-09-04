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
struct img_hash_request_ctx {int /*<<< orphan*/  digsize; int /*<<< orphan*/  digest; } ;
struct ahash_request {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int EINVAL ; 
 struct img_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int img_hash_finish(struct ahash_request *req)
{
	struct img_hash_request_ctx *ctx = ahash_request_ctx(req);

	if (!req->result)
		return -EINVAL;

	memcpy(req->result, ctx->digest, ctx->digsize);

	return 0;
}