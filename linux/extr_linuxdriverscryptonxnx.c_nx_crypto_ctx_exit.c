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
struct nx_crypto_ctx {int /*<<< orphan*/ * out_sg; int /*<<< orphan*/ * in_sg; int /*<<< orphan*/ * csbcpb_aead; int /*<<< orphan*/ * csbcpb; int /*<<< orphan*/  kmem; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct nx_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

void nx_crypto_ctx_exit(struct crypto_tfm *tfm)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(tfm);

	kzfree(nx_ctx->kmem);
	nx_ctx->csbcpb = NULL;
	nx_ctx->csbcpb_aead = NULL;
	nx_ctx->in_sg = NULL;
	nx_ctx->out_sg = NULL;
}