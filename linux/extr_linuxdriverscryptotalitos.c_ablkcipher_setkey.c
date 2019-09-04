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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct talitos_ctx {int keylen; int /*<<< orphan*/  key; int /*<<< orphan*/  dma_key; struct device* dev; } ;
struct device {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 unsigned int TALITOS_MAX_KEY_SIZE ; 
 struct talitos_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_get_flags (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ablkcipher_setkey(struct crypto_ablkcipher *cipher,
			     const u8 *key, unsigned int keylen)
{
	struct talitos_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	struct device *dev = ctx->dev;
	u32 tmp[DES_EXPKEY_WORDS];

	if (keylen > TALITOS_MAX_KEY_SIZE) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	if (unlikely(crypto_ablkcipher_get_flags(cipher) &
		     CRYPTO_TFM_REQ_WEAK_KEY) &&
	    !des_ekey(tmp, key)) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_WEAK_KEY);
		return -EINVAL;
	}

	if (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	memcpy(&ctx->key, key, keylen);
	ctx->keylen = keylen;

	ctx->dma_key = dma_map_single(dev, ctx->key, keylen, DMA_TO_DEVICE);

	return 0;
}