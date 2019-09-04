#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int crt_flags; } ;
struct crypto_ablkcipher {TYPE_1__ base; } ;
struct TYPE_5__ {unsigned int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  key_sg; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_2__ des3; } ;
struct ccp_ctx {TYPE_3__ u; } ;
struct ccp_crypto_ablkcipher_alg {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_DES3_TYPE_168 ; 
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int EINVAL ; 
 struct ccp_crypto_ablkcipher_alg* ccp_crypto_ablkcipher_alg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ccp_des3_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
		unsigned int key_len)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(crypto_ablkcipher_tfm(tfm));
	struct ccp_crypto_ablkcipher_alg *alg =
		ccp_crypto_ablkcipher_alg(crypto_ablkcipher_tfm(tfm));
	u32 *flags = &tfm->base.crt_flags;


	/* From des_generic.c:
	 *
	 * RFC2451:
	 *   If the first two or last two independent 64-bit keys are
	 *   equal (k1 == k2 or k2 == k3), then the DES3 operation is simply the
	 *   same as DES.  Implementers MUST reject keys that exhibit this
	 *   property.
	 */
	const u32 *K = (const u32 *)key;

	if (unlikely(!((K[0] ^ K[2]) | (K[1] ^ K[3])) ||
		     !((K[2] ^ K[4]) | (K[3] ^ K[5]))) &&
		     (*flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
		*flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	/* It's not clear that there is any support for a keysize of 112.
	 * If needed, the caller should make K1 == K3
	 */
	ctx->u.des3.type = CCP_DES3_TYPE_168;
	ctx->u.des3.mode = alg->mode;
	ctx->u.des3.key_len = key_len;

	memcpy(ctx->u.des3.key, key, key_len);
	sg_init_one(&ctx->u.des3.key_sg, ctx->u.des3.key, key_len);

	return 0;
}