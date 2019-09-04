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
struct aesbs_xts_ctx {int /*<<< orphan*/  tweak_tfm; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aesbs_xts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int xts_init(struct crypto_tfm *tfm)
{
	struct aesbs_xts_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->tweak_tfm = crypto_alloc_cipher("aes", 0, 0);

	return PTR_ERR_OR_ZERO(ctx->tweak_tfm);
}