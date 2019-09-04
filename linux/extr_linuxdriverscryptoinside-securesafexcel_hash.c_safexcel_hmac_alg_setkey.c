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
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_crypto_priv {int flags; } ;
struct safexcel_ahash_export_state {int /*<<< orphan*/ * state; } ;
struct TYPE_2__ {int needs_inv; scalar_t__ ctxr; } ;
struct safexcel_ahash_ctx {scalar_t__* ipad; scalar_t__* opad; TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int EIP197_TRC_CACHE ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct safexcel_ahash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ **,unsigned int) ; 
 int safexcel_hmac_setkey (char const*,int /*<<< orphan*/  const*,unsigned int,struct safexcel_ahash_export_state*,struct safexcel_ahash_export_state*) ; 

__attribute__((used)) static int safexcel_hmac_alg_setkey(struct crypto_ahash *tfm, const u8 *key,
				    unsigned int keylen, const char *alg,
				    unsigned int state_sz)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct safexcel_ahash_export_state istate, ostate;
	int ret, i;

	ret = safexcel_hmac_setkey(alg, key, keylen, &istate, &ostate);
	if (ret)
		return ret;

	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr) {
		for (i = 0; i < state_sz / sizeof(u32); i++) {
			if (ctx->ipad[i] != le32_to_cpu(istate.state[i]) ||
			    ctx->opad[i] != le32_to_cpu(ostate.state[i])) {
				ctx->base.needs_inv = true;
				break;
			}
		}
	}

	memcpy(ctx->ipad, &istate.state, state_sz);
	memcpy(ctx->opad, &ostate.state, state_sz);

	return 0;
}