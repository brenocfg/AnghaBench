#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct artpec6_hash_request_context {TYPE_1__ common; } ;
struct ahash_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  ARTPEC6_CRYPTO_PREPARE_HASH_NO_START 129 
#define  ARTPEC6_CRYPTO_PREPARE_HASH_START 128 
 struct artpec6_hash_request_context* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  artpec6_crypto_common_destroy (TYPE_1__*) ; 
 int artpec6_crypto_common_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  artpec6_crypto_complete_hash ; 
 int artpec6_crypto_prepare_hash (struct ahash_request*) ; 
 int artpec6_crypto_submit (TYPE_1__*) ; 

__attribute__((used)) static int artpec6_crypto_prepare_submit_hash(struct ahash_request *req)
{
	struct artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);
	int ret;

	if (!req_ctx->common.dma) {
		ret = artpec6_crypto_common_init(&req_ctx->common,
					  &req->base,
					  artpec6_crypto_complete_hash,
					  NULL, 0);

		if (ret)
			return ret;
	}

	ret = artpec6_crypto_prepare_hash(req);
	switch (ret) {
	case ARTPEC6_CRYPTO_PREPARE_HASH_START:
		ret = artpec6_crypto_submit(&req_ctx->common);
		break;

	case ARTPEC6_CRYPTO_PREPARE_HASH_NO_START:
		ret = 0;
		/* Fallthrough */

	default:
		artpec6_crypto_common_destroy(&req_ctx->common);
		break;
	}

	return ret;
}