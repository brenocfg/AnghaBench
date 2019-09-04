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
typedef  int /*<<< orphan*/  u8 ;
struct ppc_aes_ctx {int /*<<< orphan*/  rounds; int /*<<< orphan*/  key_enc; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct ppc_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ppc_encrypt_aes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spe_begin () ; 
 int /*<<< orphan*/  spe_end () ; 

__attribute__((used)) static void ppc_aes_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct ppc_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	spe_begin();
	ppc_encrypt_aes(out, in, ctx->key_enc, ctx->rounds);
	spe_end();
}