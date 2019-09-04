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
struct s390_pxts_ctx {TYPE_2__* pk; TYPE_1__* sk; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  const* protkey; } ;
struct TYPE_3__ {int /*<<< orphan*/ * seckey; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int AES_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 scalar_t__ PKEY_KEYTYPE_AES_128 ; 
 int SECKEYBLOBSIZE ; 
 scalar_t__ __xts_paes_set_key (struct s390_pxts_ctx*) ; 
 struct s390_pxts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int xts_check_key (struct crypto_tfm*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int xts_paes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			    unsigned int key_len)
{
	struct s390_pxts_ctx *ctx = crypto_tfm_ctx(tfm);
	u8 ckey[2 * AES_MAX_KEY_SIZE];
	unsigned int ckey_len;

	memcpy(ctx->sk[0].seckey, in_key, SECKEYBLOBSIZE);
	memcpy(ctx->sk[1].seckey, in_key + SECKEYBLOBSIZE, SECKEYBLOBSIZE);
	if (__xts_paes_set_key(ctx)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	/*
	 * xts_check_key verifies the key length is not odd and makes
	 * sure that the two keys are not the same. This can be done
	 * on the two protected keys as well
	 */
	ckey_len = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ?
		AES_KEYSIZE_128 : AES_KEYSIZE_256;
	memcpy(ckey, ctx->pk[0].protkey, ckey_len);
	memcpy(ckey + ckey_len, ctx->pk[1].protkey, ckey_len);
	return xts_check_key(tfm, ckey, 2*ckey_len);
}