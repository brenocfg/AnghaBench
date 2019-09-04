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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_tfm {int dummy; } ;
struct crypto_sm4_ctx {int /*<<< orphan*/  rkey_enc; } ;

/* Variables and functions */
 struct crypto_sm4_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  sm4_do_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void crypto_sm4_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	const struct crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);

	sm4_do_crypt(ctx->rkey_enc, (u32 *)out, (u32 *)in);
}