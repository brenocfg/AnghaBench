#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {struct aead_request* aead_req; } ;
struct crypt_ctl {int /*<<< orphan*/  icv_rev_aes; TYPE_1__ data; } ;
struct aead_request {int assoclen; int cryptlen; int /*<<< orphan*/  dst; } ;
struct aead_ctx {int /*<<< orphan*/  hmac_virt; scalar_t__ encrypt; } ;

/* Variables and functions */
 struct aead_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  buffer_pool ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void finish_scattered_hmac(struct crypt_ctl *crypt)
{
	struct aead_request *req = crypt->data.aead_req;
	struct aead_ctx *req_ctx = aead_request_ctx(req);
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	int authsize = crypto_aead_authsize(tfm);
	int decryptlen = req->assoclen + req->cryptlen - authsize;

	if (req_ctx->encrypt) {
		scatterwalk_map_and_copy(req_ctx->hmac_virt,
			req->dst, decryptlen, authsize, 1);
	}
	dma_pool_free(buffer_pool, req_ctx->hmac_virt, crypt->icv_rev_aes);
}