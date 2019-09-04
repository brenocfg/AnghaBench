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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {unsigned int keylen; } ;
struct caam_ctx {TYPE_1__ cdata; int /*<<< orphan*/  dir; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key; struct device* jrdev; } ;

/* Variables and functions */
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int gcm_set_sh_desc (struct crypto_aead*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int gcm_setkey(struct crypto_aead *aead,
		      const u8 *key, unsigned int keylen)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "key in @"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key, keylen, 1);
#endif

	memcpy(ctx->key, key, keylen);
	dma_sync_single_for_device(jrdev, ctx->key_dma, keylen, ctx->dir);
	ctx->cdata.keylen = keylen;

	return gcm_set_sh_desc(aead);
}