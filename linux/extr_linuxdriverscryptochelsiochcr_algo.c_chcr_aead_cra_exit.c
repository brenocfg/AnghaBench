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
struct chcr_aead_ctx {int /*<<< orphan*/  sw_cipher; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chcr_aead_cra_exit(struct crypto_aead *tfm)
{
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	crypto_free_aead(aeadctx->sw_cipher);
}