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
struct vmac_tfm_ctx {int /*<<< orphan*/  polykey; } ;
struct vmac_desc_ctx {int first_block_processed; scalar_t__ nonce_size; int /*<<< orphan*/  polytmp; scalar_t__ partial_size; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 struct vmac_tfm_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vmac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int vmac_init(struct shash_desc *desc)
{
	const struct vmac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	struct vmac_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->partial_size = 0;
	dctx->first_block_processed = false;
	memcpy(dctx->polytmp, tctx->polykey, sizeof(dctx->polytmp));
	dctx->nonce_size = 0;
	return 0;
}