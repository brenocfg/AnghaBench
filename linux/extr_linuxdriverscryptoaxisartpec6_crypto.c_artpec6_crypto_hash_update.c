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
struct artpec6_hash_request_context {int /*<<< orphan*/  hash_flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FLAG_UPDATE ; 
 struct artpec6_hash_request_context* ahash_request_ctx (struct ahash_request*) ; 
 int artpec6_crypto_prepare_submit_hash (struct ahash_request*) ; 

__attribute__((used)) static int artpec6_crypto_hash_update(struct ahash_request *req)
{
	struct artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);

	req_ctx->hash_flags |= HASH_FLAG_UPDATE;

	return artpec6_crypto_prepare_submit_hash(req);
}