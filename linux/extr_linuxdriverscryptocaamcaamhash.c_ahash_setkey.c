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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int key_inline; unsigned int keylen; scalar_t__ keylen_pad; int algtype; } ;
struct caam_hash_ctx {TYPE_2__ adata; int /*<<< orphan*/  key; TYPE_1__* jrdev; } ;
struct caam_drv_private {int era; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ CAAM_MAX_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int OP_ALG_ALGSEL_MASK ; 
 int ahash_set_sh_desc (struct crypto_ahash*) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int crypto_tfm_alg_blocksize (int /*<<< orphan*/ *) ; 
 struct caam_drv_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int gen_split_key (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/  const*,unsigned int,scalar_t__) ; 
 int hash_digest_key (struct caam_hash_ctx*,int /*<<< orphan*/  const*,unsigned int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ split_key_len (int) ; 

__attribute__((used)) static int ahash_setkey(struct crypto_ahash *ahash,
			const u8 *key, unsigned int keylen)
{
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	int blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	int digestsize = crypto_ahash_digestsize(ahash);
	struct caam_drv_private *ctrlpriv = dev_get_drvdata(ctx->jrdev->parent);
	int ret;
	u8 *hashed_key = NULL;

#ifdef DEBUG
	printk(KERN_ERR "keylen %d\n", keylen);
#endif

	if (keylen > blocksize) {
		hashed_key = kmalloc_array(digestsize,
					   sizeof(*hashed_key),
					   GFP_KERNEL | GFP_DMA);
		if (!hashed_key)
			return -ENOMEM;
		ret = hash_digest_key(ctx, key, &keylen, hashed_key,
				      digestsize);
		if (ret)
			goto bad_free_key;
		key = hashed_key;
	}

	/*
	 * If DKP is supported, use it in the shared descriptor to generate
	 * the split key.
	 */
	if (ctrlpriv->era >= 6) {
		ctx->adata.key_inline = true;
		ctx->adata.keylen = keylen;
		ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
						      OP_ALG_ALGSEL_MASK);

		if (ctx->adata.keylen_pad > CAAM_MAX_HASH_KEY_SIZE)
			goto bad_free_key;

		memcpy(ctx->key, key, keylen);
	} else {
		ret = gen_split_key(ctx->jrdev, ctx->key, &ctx->adata, key,
				    keylen, CAAM_MAX_HASH_KEY_SIZE);
		if (ret)
			goto bad_free_key;
	}

	kfree(hashed_key);
	return ahash_set_sh_desc(ahash);
 bad_free_key:
	kfree(hashed_key);
	crypto_ahash_set_flags(ahash, CRYPTO_TFM_RES_BAD_KEY_LEN);
	return -EINVAL;
}