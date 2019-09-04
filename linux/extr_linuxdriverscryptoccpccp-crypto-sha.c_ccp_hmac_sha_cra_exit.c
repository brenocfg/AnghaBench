#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_tfm {int dummy; } ;
struct TYPE_3__ {scalar_t__ hmac_tfm; } ;
struct TYPE_4__ {TYPE_1__ sha; } ;
struct ccp_ctx {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_sha_cra_exit (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 struct ccp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void ccp_hmac_sha_cra_exit(struct crypto_tfm *tfm)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(tfm);

	if (ctx->u.sha.hmac_tfm)
		crypto_free_shash(ctx->u.sha.hmac_tfm);

	ccp_sha_cra_exit(tfm);
}