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
struct chcr_aead_reqctx {int* iv; scalar_t__ scratch_pad; } ;
struct chcr_aead_ctx {int /*<<< orphan*/ * salt; } ;
struct aead_request {int /*<<< orphan*/ * iv; } ;

/* Variables and functions */
 unsigned int CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309 ; 
 struct chcr_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  generate_b0 (struct aead_request*,struct chcr_aead_ctx*,unsigned short) ; 
 unsigned short htons (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccm_format_packet(struct aead_request *req,
			     struct chcr_aead_ctx *aeadctx,
			     unsigned int sub_type,
			     unsigned short op_type,
			     unsigned int assoclen)
{
	struct chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	int rc = 0;

	if (sub_type == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309) {
		reqctx->iv[0] = 3;
		memcpy(reqctx->iv + 1, &aeadctx->salt[0], 3);
		memcpy(reqctx->iv + 4, req->iv, 8);
		memset(reqctx->iv + 12, 0, 4);
	} else {
		memcpy(reqctx->iv, req->iv, 16);
	}
	if (assoclen)
		*((unsigned short *)(reqctx->scratch_pad + 16)) =
				htons(assoclen);

	generate_b0(req, aeadctx, op_type);
	/* zero the ctr value */
	memset(reqctx->iv + 15 - reqctx->iv[0], 0, reqctx->iv[0] + 1);
	return rc;
}