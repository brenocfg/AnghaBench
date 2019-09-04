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
struct crypto_ctx_hdr {int /*<<< orphan*/  dma; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct crypto_ctx_hdr*) ; 

void crypto_free_context(void *ctx)
{
	struct crypto_ctx_hdr *ctxp;

	if (!ctx)
		return;

	ctxp = ctx;
	dma_pool_free(ctxp->pool, ctxp->vaddr, ctxp->dma);
	kfree(ctxp);
}