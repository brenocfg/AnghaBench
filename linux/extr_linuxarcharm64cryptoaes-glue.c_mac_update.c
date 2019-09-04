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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct mac_tfm_ctx {int /*<<< orphan*/  key; } ;
struct mac_desc_ctx {unsigned int len; scalar_t__ dg; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 struct mac_tfm_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_xor (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  mac_do_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,scalar_t__,int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct mac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int mac_update(struct shash_desc *desc, const u8 *p, unsigned int len)
{
	struct mac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	struct mac_desc_ctx *ctx = shash_desc_ctx(desc);

	while (len > 0) {
		unsigned int l;

		if ((ctx->len % AES_BLOCK_SIZE) == 0 &&
		    (ctx->len + len) > AES_BLOCK_SIZE) {

			int blocks = len / AES_BLOCK_SIZE;

			len %= AES_BLOCK_SIZE;

			mac_do_update(&tctx->key, p, blocks, ctx->dg,
				      (ctx->len != 0), (len != 0));

			p += blocks * AES_BLOCK_SIZE;

			if (!len) {
				ctx->len = AES_BLOCK_SIZE;
				break;
			}
			ctx->len = 0;
		}

		l = min(len, AES_BLOCK_SIZE - ctx->len);

		if (l <= AES_BLOCK_SIZE) {
			crypto_xor(ctx->dg + ctx->len, p, l);
			ctx->len += l;
			len -= l;
			p += l;
		}
	}

	return 0;
}