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
struct nx_crypto_ctx {int /*<<< orphan*/  csbcpb; int /*<<< orphan*/ * props; int /*<<< orphan*/ * ap; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCOP_FC_SHA ; 
 int /*<<< orphan*/  NX_CPB_SET_DIGEST_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_DS_SHA256 ; 
 size_t NX_PROPS_SHA256 ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int nx_crypto_ctx_sha_init (struct crypto_tfm*) ; 
 int /*<<< orphan*/  nx_ctx_init (struct nx_crypto_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nx_crypto_ctx_sha256_init(struct crypto_tfm *tfm)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(tfm);
	int err;

	err = nx_crypto_ctx_sha_init(tfm);
	if (err)
		return err;

	nx_ctx_init(nx_ctx, HCOP_FC_SHA);

	nx_ctx->ap = &nx_ctx->props[NX_PROPS_SHA256];

	NX_CPB_SET_DIGEST_SIZE(nx_ctx->csbcpb, NX_DS_SHA256);

	return 0;
}