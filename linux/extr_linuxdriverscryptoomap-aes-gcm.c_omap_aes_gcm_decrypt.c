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
struct omap_aes_reqctx {int /*<<< orphan*/  iv; } ;
struct aead_request {int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_GCM ; 
 int /*<<< orphan*/  GCM_AES_IV_SIZE ; 
 struct omap_aes_reqctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_aes_gcm_crypt (struct aead_request*,int /*<<< orphan*/ ) ; 

int omap_aes_gcm_decrypt(struct aead_request *req)
{
	struct omap_aes_reqctx *rctx = aead_request_ctx(req);

	memcpy(rctx->iv, req->iv, GCM_AES_IV_SIZE);
	return omap_aes_gcm_crypt(req, FLAGS_GCM);
}