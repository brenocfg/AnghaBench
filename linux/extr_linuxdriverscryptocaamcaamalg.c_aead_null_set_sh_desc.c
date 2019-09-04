#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  parent; } ;
struct crypto_aead {int dummy; } ;
struct caam_drv_private {int /*<<< orphan*/  era; } ;
struct TYPE_3__ {int keylen_pad; int key_inline; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key_virt; } ;
struct caam_ctx {int /*<<< orphan*/  dir; int /*<<< orphan*/  sh_desc_dec_dma; int /*<<< orphan*/  authsize; TYPE_1__ adata; int /*<<< orphan*/ * sh_desc_dec; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key; int /*<<< orphan*/  sh_desc_enc_dma; int /*<<< orphan*/ * sh_desc_enc; struct device* jrdev; } ;

/* Variables and functions */
 int AEAD_DESC_JOB_IO_LEN ; 
 int CAAM_DESC_BYTES_MAX ; 
 int DESC_AEAD_NULL_DEC_LEN ; 
 int DESC_AEAD_NULL_ENC_LEN ; 
 int /*<<< orphan*/  cnstr_shdsc_aead_null_decap (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnstr_shdsc_aead_null_encap (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  desc_bytes (int /*<<< orphan*/ *) ; 
 struct caam_drv_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aead_null_set_sh_desc(struct crypto_aead *aead)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;
	struct caam_drv_private *ctrlpriv = dev_get_drvdata(jrdev->parent);
	u32 *desc;
	int rem_bytes = CAAM_DESC_BYTES_MAX - AEAD_DESC_JOB_IO_LEN -
			ctx->adata.keylen_pad;

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit into the 64-word Descriptor h/w Buffer
	 */
	if (rem_bytes >= DESC_AEAD_NULL_ENC_LEN) {
		ctx->adata.key_inline = true;
		ctx->adata.key_virt = ctx->key;
	} else {
		ctx->adata.key_inline = false;
		ctx->adata.key_dma = ctx->key_dma;
	}

	/* aead_encrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_aead_null_encap(desc, &ctx->adata, ctx->authsize,
				    ctrlpriv->era);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit into the 64-word Descriptor h/w Buffer
	 */
	if (rem_bytes >= DESC_AEAD_NULL_DEC_LEN) {
		ctx->adata.key_inline = true;
		ctx->adata.key_virt = ctx->key;
	} else {
		ctx->adata.key_inline = false;
		ctx->adata.key_dma = ctx->key_dma;
	}

	/* aead_decrypt shared descriptor */
	desc = ctx->sh_desc_dec;
	cnstr_shdsc_aead_null_decap(desc, &ctx->adata, ctx->authsize,
				    ctrlpriv->era);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	return 0;
}