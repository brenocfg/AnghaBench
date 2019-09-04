#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  parent; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_virt; } ;
struct caam_hash_ctx {int ctx_len; int /*<<< orphan*/  dir; int /*<<< orphan*/  sh_desc_digest_dma; int /*<<< orphan*/ * sh_desc_digest; int /*<<< orphan*/  sh_desc_fin_dma; int /*<<< orphan*/ * sh_desc_fin; int /*<<< orphan*/  sh_desc_update_first_dma; int /*<<< orphan*/ * sh_desc_update_first; int /*<<< orphan*/  sh_desc_update_dma; int /*<<< orphan*/ * sh_desc_update; int /*<<< orphan*/  key; TYPE_1__ adata; struct device* jrdev; } ;
struct caam_drv_private {int /*<<< orphan*/  era; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ALG_AS_FINALIZE ; 
 int /*<<< orphan*/  OP_ALG_AS_INIT ; 
 int /*<<< orphan*/  OP_ALG_AS_INITFINAL ; 
 int /*<<< orphan*/  OP_ALG_AS_UPDATE ; 
 int /*<<< orphan*/  ahash_gen_sh_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct caam_hash_ctx*,int,int /*<<< orphan*/ ) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  desc_bytes (int /*<<< orphan*/ *) ; 
 struct caam_drv_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_set_sh_desc(struct crypto_ahash *ahash)
{
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	int digestsize = crypto_ahash_digestsize(ahash);
	struct device *jrdev = ctx->jrdev;
	struct caam_drv_private *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 *desc;

	ctx->adata.key_virt = ctx->key;

	/* ahash_update shared descriptor */
	desc = ctx->sh_desc_update;
	ahash_gen_sh_desc(desc, OP_ALG_AS_UPDATE, ctx->ctx_len, ctx, true,
			  ctrlpriv->era);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_update_dma,
				   desc_bytes(desc), ctx->dir);
#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "ahash update shdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif

	/* ahash_update_first shared descriptor */
	desc = ctx->sh_desc_update_first;
	ahash_gen_sh_desc(desc, OP_ALG_AS_INIT, ctx->ctx_len, ctx, false,
			  ctrlpriv->era);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_update_first_dma,
				   desc_bytes(desc), ctx->dir);
#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "ahash update first shdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif

	/* ahash_final shared descriptor */
	desc = ctx->sh_desc_fin;
	ahash_gen_sh_desc(desc, OP_ALG_AS_FINALIZE, digestsize, ctx, true,
			  ctrlpriv->era);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_fin_dma,
				   desc_bytes(desc), ctx->dir);
#ifdef DEBUG
	print_hex_dump(KERN_ERR, "ahash final shdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc,
		       desc_bytes(desc), 1);
#endif

	/* ahash_digest shared descriptor */
	desc = ctx->sh_desc_digest;
	ahash_gen_sh_desc(desc, OP_ALG_AS_INITFINAL, digestsize, ctx, false,
			  ctrlpriv->era);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_digest_dma,
				   desc_bytes(desc), ctx->dir);
#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "ahash digest shdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc,
		       desc_bytes(desc), 1);
#endif

	return 0;
}