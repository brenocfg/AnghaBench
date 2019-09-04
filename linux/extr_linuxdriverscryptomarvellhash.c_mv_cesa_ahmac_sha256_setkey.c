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
struct sha256_state {int /*<<< orphan*/ * state; } ;
struct mv_cesa_hmac_ctx {void** iv; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct mv_cesa_hmac_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int mv_cesa_ahmac_setkey (char*,int /*<<< orphan*/  const*,unsigned int,struct sha256_state*,struct sha256_state*) ; 

__attribute__((used)) static int mv_cesa_ahmac_sha256_setkey(struct crypto_ahash *tfm, const u8 *key,
				       unsigned int keylen)
{
	struct mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct sha256_state istate, ostate;
	int ret, i;

	ret = mv_cesa_ahmac_setkey("mv-sha256", key, keylen, &istate, &ostate);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(istate.state); i++)
		ctx->iv[i] = be32_to_cpu(istate.state[i]);

	for (i = 0; i < ARRAY_SIZE(ostate.state); i++)
		ctx->iv[i + 8] = be32_to_cpu(ostate.state[i]);

	return 0;
}