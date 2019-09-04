#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct device {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct TYPE_4__ {int algtype; unsigned int keylen; int key_inline; int /*<<< orphan*/  const* key_virt; } ;
struct caam_ctx {int* sh_desc_enc; int* sh_desc_dec; int* sh_desc_givenc; int /*<<< orphan*/  dir; int /*<<< orphan*/  sh_desc_givenc_dma; TYPE_1__ cdata; int /*<<< orphan*/  sh_desc_dec_dma; int /*<<< orphan*/  sh_desc_enc_dma; struct device* jrdev; } ;

/* Variables and functions */
 int CTR_RFC3686_NONCE_SIZE ; 
 int OP_ALG_AAI_CTR_MOD128 ; 
 int OP_ALG_AAI_MASK ; 
 int /*<<< orphan*/  cnstr_shdsc_ablkcipher_decap (int*,TYPE_1__*,unsigned int,int const,int) ; 
 int /*<<< orphan*/  cnstr_shdsc_ablkcipher_encap (int*,TYPE_1__*,unsigned int,int const,int) ; 
 int /*<<< orphan*/  cnstr_shdsc_ablkcipher_givencap (int*,TYPE_1__*,unsigned int,int const,int) ; 
 struct caam_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 int /*<<< orphan*/  desc_bytes (int*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static int ablkcipher_setkey(struct crypto_ablkcipher *ablkcipher,
			     const u8 *key, unsigned int keylen)
{
	struct caam_ctx *ctx = crypto_ablkcipher_ctx(ablkcipher);
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(ablkcipher);
	const char *alg_name = crypto_tfm_alg_name(tfm);
	struct device *jrdev = ctx->jrdev;
	unsigned int ivsize = crypto_ablkcipher_ivsize(ablkcipher);
	u32 *desc;
	u32 ctx1_iv_off = 0;
	const bool ctr_mode = ((ctx->cdata.algtype & OP_ALG_AAI_MASK) ==
			       OP_ALG_AAI_CTR_MOD128);
	const bool is_rfc3686 = (ctr_mode &&
				 (strstr(alg_name, "rfc3686") != NULL));

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "key in @"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);
#endif
	/*
	 * AES-CTR needs to load IV in CONTEXT1 reg
	 * at an offset of 128bits (16bytes)
	 * CONTEXT1[255:128] = IV
	 */
	if (ctr_mode)
		ctx1_iv_off = 16;

	/*
	 * RFC3686 specific:
	 *	| CONTEXT1[255:128] = {NONCE, IV, COUNTER}
	 *	| *key = {KEY, NONCE}
	 */
	if (is_rfc3686) {
		ctx1_iv_off = 16 + CTR_RFC3686_NONCE_SIZE;
		keylen -= CTR_RFC3686_NONCE_SIZE;
	}

	ctx->cdata.keylen = keylen;
	ctx->cdata.key_virt = key;
	ctx->cdata.key_inline = true;

	/* ablkcipher_encrypt shared descriptor */
	desc = ctx->sh_desc_enc;
	cnstr_shdsc_ablkcipher_encap(desc, &ctx->cdata, ivsize, is_rfc3686,
				     ctx1_iv_off);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	/* ablkcipher_decrypt shared descriptor */
	desc = ctx->sh_desc_dec;
	cnstr_shdsc_ablkcipher_decap(desc, &ctx->cdata, ivsize, is_rfc3686,
				     ctx1_iv_off);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	/* ablkcipher_givencrypt shared descriptor */
	desc = ctx->sh_desc_givenc;
	cnstr_shdsc_ablkcipher_givencap(desc, &ctx->cdata, ivsize, is_rfc3686,
					ctx1_iv_off);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_givenc_dma,
				   desc_bytes(desc), ctx->dir);

	return 0;
}