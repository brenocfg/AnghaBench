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
struct des3_ede_x86_ctx {int* enc_expkey; int* dec_expkey; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
 int DES3_EDE_EXPKEY_WORDS ; 
 int __des3_ede_setkey (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct des3_ede_x86_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int ror32 (int,int) ; 

__attribute__((used)) static int des3_ede_x86_setkey(struct crypto_tfm *tfm, const u8 *key,
			       unsigned int keylen)
{
	struct des3_ede_x86_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 i, j, tmp;
	int err;

	/* Generate encryption context using generic implementation. */
	err = __des3_ede_setkey(ctx->enc_expkey, &tfm->crt_flags, key, keylen);
	if (err < 0)
		return err;

	/* Fix encryption context for this implementation and form decryption
	 * context. */
	j = DES3_EDE_EXPKEY_WORDS - 2;
	for (i = 0; i < DES3_EDE_EXPKEY_WORDS; i += 2, j -= 2) {
		tmp = ror32(ctx->enc_expkey[i + 1], 4);
		ctx->enc_expkey[i + 1] = tmp;

		ctx->dec_expkey[j + 0] = ctx->enc_expkey[i + 0];
		ctx->dec_expkey[j + 1] = tmp;
	}

	return 0;
}