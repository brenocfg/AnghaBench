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
struct blkcipher_desc {int /*<<< orphan*/  info; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int ccm_nx_encrypt (struct aead_request*,struct blkcipher_desc*,int /*<<< orphan*/ ) ; 
 int crypto_ccm_check_iv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccm_aes_nx_encrypt(struct aead_request *req)
{
	struct blkcipher_desc desc;
	int rc;

	desc.info = req->iv;

	rc = crypto_ccm_check_iv(desc.info);
	if (rc)
		return rc;

	return ccm_nx_encrypt(req, &desc, req->assoclen);
}