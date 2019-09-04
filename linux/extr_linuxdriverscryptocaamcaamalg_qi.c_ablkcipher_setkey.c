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
struct caam_ctx {int /*<<< orphan*/  sh_desc_givenc; scalar_t__* drv_ctx; int /*<<< orphan*/  sh_desc_dec; int /*<<< orphan*/  sh_desc_enc; TYPE_1__ cdata; struct device* jrdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 size_t DECRYPT ; 
 int EINVAL ; 
 size_t ENCRYPT ; 
 size_t GIVENCRYPT ; 
 int OP_ALG_AAI_CTR_MOD128 ; 
 int OP_ALG_AAI_MASK ; 
 int caam_drv_ctx_update (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnstr_shdsc_ablkcipher_decap (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int const,int) ; 
 int /*<<< orphan*/  cnstr_shdsc_ablkcipher_encap (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int const,int) ; 
 int /*<<< orphan*/  cnstr_shdsc_ablkcipher_givencap (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int const,int) ; 
 struct caam_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static int ablkcipher_setkey(struct crypto_ablkcipher *ablkcipher,
			     const u8 *key, unsigned int keylen)
{
	struct caam_ctx *ctx = crypto_ablkcipher_ctx(ablkcipher);
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(ablkcipher);
	const char *alg_name = crypto_tfm_alg_name(tfm);
	struct device *jrdev = ctx->jrdev;
	unsigned int ivsize = crypto_ablkcipher_ivsize(ablkcipher);
	u32 ctx1_iv_off = 0;
	const bool ctr_mode = ((ctx->cdata.algtype & OP_ALG_AAI_MASK) ==
			       OP_ALG_AAI_CTR_MOD128);
	const bool is_rfc3686 = (ctr_mode && strstr(alg_name, "rfc3686"));
	int ret = 0;

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "key in @" __stringify(__LINE__)": ",
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

	/* ablkcipher encrypt, decrypt, givencrypt shared descriptors */
	cnstr_shdsc_ablkcipher_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				     is_rfc3686, ctx1_iv_off);
	cnstr_shdsc_ablkcipher_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				     is_rfc3686, ctx1_iv_off);
	cnstr_shdsc_ablkcipher_givencap(ctx->sh_desc_givenc, &ctx->cdata,
					ivsize, is_rfc3686, ctx1_iv_off);

	/* Now update the driver contexts with the new shared descriptor */
	if (ctx->drv_ctx[ENCRYPT]) {
		ret = caam_drv_ctx_update(ctx->drv_ctx[ENCRYPT],
					  ctx->sh_desc_enc);
		if (ret) {
			dev_err(jrdev, "driver enc context update failed\n");
			goto badkey;
		}
	}

	if (ctx->drv_ctx[DECRYPT]) {
		ret = caam_drv_ctx_update(ctx->drv_ctx[DECRYPT],
					  ctx->sh_desc_dec);
		if (ret) {
			dev_err(jrdev, "driver dec context update failed\n");
			goto badkey;
		}
	}

	if (ctx->drv_ctx[GIVENCRYPT]) {
		ret = caam_drv_ctx_update(ctx->drv_ctx[GIVENCRYPT],
					  ctx->sh_desc_givenc);
		if (ret) {
			dev_err(jrdev, "driver givenc context update failed\n");
			goto badkey;
		}
	}

	return ret;
badkey:
	crypto_ablkcipher_set_flags(ablkcipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
	return -EINVAL;
}