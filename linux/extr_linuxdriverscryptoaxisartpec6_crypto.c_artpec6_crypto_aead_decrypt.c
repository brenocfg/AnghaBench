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
struct artpec6_crypto_aead_req_ctx {int decrypt; int /*<<< orphan*/  common; } ;
struct aead_request {scalar_t__ cryptlen; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int EINVAL ; 
 struct artpec6_crypto_aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  artpec6_crypto_common_destroy (int /*<<< orphan*/ *) ; 
 int artpec6_crypto_common_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  artpec6_crypto_complete_aead ; 
 int artpec6_crypto_prepare_aead (struct aead_request*) ; 
 int artpec6_crypto_submit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int artpec6_crypto_aead_decrypt(struct aead_request *req)
{
	int ret;
	struct artpec6_crypto_aead_req_ctx *req_ctx = aead_request_ctx(req);

	req_ctx->decrypt = true;
	if (req->cryptlen < AES_BLOCK_SIZE)
		return -EINVAL;

	ret = artpec6_crypto_common_init(&req_ctx->common,
				  &req->base,
				  artpec6_crypto_complete_aead,
				  NULL, 0);
	if (ret)
		return ret;

	ret = artpec6_crypto_prepare_aead(req);
	if (ret) {
		artpec6_crypto_common_destroy(&req_ctx->common);
		return ret;
	}

	return artpec6_crypto_submit(&req_ctx->common);
}