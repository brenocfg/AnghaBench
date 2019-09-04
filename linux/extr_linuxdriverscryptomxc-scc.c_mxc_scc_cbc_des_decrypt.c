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
struct mxc_scc_ctx {int /*<<< orphan*/  ctrl; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCC_SCM_CTRL_CBC_MODE ; 
 int /*<<< orphan*/  SCC_SCM_CTRL_DECRYPT_MODE ; 
 int /*<<< orphan*/  SCC_SCM_CTRL_START_CIPHER ; 
 struct mxc_scc_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int mxc_scc_des3_op (struct mxc_scc_ctx*,struct ablkcipher_request*) ; 

__attribute__((used)) static int mxc_scc_cbc_des_decrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(req);
	struct mxc_scc_ctx *ctx = crypto_ablkcipher_ctx(cipher);

	ctx->ctrl = SCC_SCM_CTRL_START_CIPHER;
	ctx->ctrl |= SCC_SCM_CTRL_CBC_MODE;
	ctx->ctrl |= SCC_SCM_CTRL_DECRYPT_MODE;

	return mxc_scc_des3_op(ctx, req);
}