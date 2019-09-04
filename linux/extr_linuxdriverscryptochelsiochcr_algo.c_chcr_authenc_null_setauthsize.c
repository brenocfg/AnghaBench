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
struct crypto_aead {int dummy; } ;
struct chcr_aead_ctx {int /*<<< orphan*/  sw_cipher; int /*<<< orphan*/  mayverify; int /*<<< orphan*/  hmac_ctrl; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHCR_SCMD_HMAC_CTRL_NOP ; 
 int /*<<< orphan*/  VERIFY_HW ; 
 int /*<<< orphan*/  a_ctx (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int chcr_authenc_null_setauthsize(struct crypto_aead *tfm,
					unsigned int authsize)
{
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NOP;
	aeadctx->mayverify = VERIFY_HW;
	return crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
}