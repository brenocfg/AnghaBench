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
struct chcr_aead_ctx {int dummy; } ;
struct aead_request {int assoclen; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 unsigned int CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309 ; 
 int EINVAL ; 
 scalar_t__ crypto_ccm_check_iv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int aead_ccm_validate_input(unsigned short op_type,
				   struct aead_request *req,
				   struct chcr_aead_ctx *aeadctx,
				   unsigned int sub_type)
{
	if (sub_type != CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309) {
		if (crypto_ccm_check_iv(req->iv)) {
			pr_err("CCM: IV check fails\n");
			return -EINVAL;
		}
	} else {
		if (req->assoclen != 16 && req->assoclen != 20) {
			pr_err("RFC4309: Invalid AAD length %d\n",
			       req->assoclen);
			return -EINVAL;
		}
	}
	return 0;
}