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
typedef  int u32 ;
struct des_sparc64_ctx {int /*<<< orphan*/ * encrypt_expkey; int /*<<< orphan*/ * decrypt_expkey; } ;
struct crypto_tfm {int crt_flags; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 int EINVAL ; 
 struct des_sparc64_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int des_ekey (int*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  des_sparc64_key_expand (int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encrypt_to_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int des_set_key(struct crypto_tfm *tfm, const u8 *key,
		       unsigned int keylen)
{
	struct des_sparc64_ctx *dctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;
	u32 tmp[DES_EXPKEY_WORDS];
	int ret;

	/* Even though we have special instructions for key expansion,
	 * we call des_ekey() so that we don't have to write our own
	 * weak key detection code.
	 */
	ret = des_ekey(tmp, key);
	if (unlikely(ret == 0) && (*flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
		*flags |= CRYPTO_TFM_RES_WEAK_KEY;
		return -EINVAL;
	}

	des_sparc64_key_expand((const u32 *) key, &dctx->encrypt_expkey[0]);
	encrypt_to_decrypt(&dctx->decrypt_expkey[0], &dctx->encrypt_expkey[0]);

	return 0;
}