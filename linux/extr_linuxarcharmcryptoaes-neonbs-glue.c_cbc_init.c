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
struct crypto_tfm {int dummy; } ;
struct aesbs_cbc_ctx {int /*<<< orphan*/  enc_tfm; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aesbs_cbc_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int cbc_init(struct crypto_tfm *tfm)
{
	struct aesbs_cbc_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->enc_tfm = crypto_alloc_cipher("aes", 0, 0);

	return PTR_ERR_OR_ZERO(ctx->enc_tfm);
}