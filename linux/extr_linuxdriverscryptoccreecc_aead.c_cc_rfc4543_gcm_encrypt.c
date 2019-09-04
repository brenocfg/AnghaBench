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
struct aead_request {int /*<<< orphan*/  iv; } ;
struct aead_req_ctx {int plaintext_authenticate_only; int is_gcm4543; int /*<<< orphan*/  backup_iv; int /*<<< orphan*/ * backup_giv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int cc_proc_aead (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_proc_rfc4_gcm (struct aead_request*) ; 

__attribute__((used)) static int cc_rfc4543_gcm_encrypt(struct aead_request *req)
{
	/* Very similar to cc_aead_encrypt() above. */

	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc;

	//plaintext is not encryped with rfc4543
	areq_ctx->plaintext_authenticate_only = true;

	/* No generated IV required */
	areq_ctx->backup_iv = req->iv;
	areq_ctx->backup_giv = NULL;

	cc_proc_rfc4_gcm(req);
	areq_ctx->is_gcm4543 = true;

	rc = cc_proc_aead(req, DRV_CRYPTO_DIRECTION_ENCRYPT);
	if (rc != -EINPROGRESS && rc != -EBUSY)
		req->iv = areq_ctx->backup_iv;

	return rc;
}