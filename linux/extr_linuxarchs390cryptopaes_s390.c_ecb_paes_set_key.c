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
struct TYPE_2__ {int /*<<< orphan*/  seckey; } ;
struct s390_paes_ctx {TYPE_1__ sk; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 unsigned int SECKEYBLOBSIZE ; 
 scalar_t__ __paes_set_key (struct s390_paes_ctx*) ; 
 struct s390_paes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int ecb_paes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			    unsigned int key_len)
{
	struct s390_paes_ctx *ctx = crypto_tfm_ctx(tfm);

	if (key_len != SECKEYBLOBSIZE)
		return -EINVAL;

	memcpy(ctx->sk.seckey, in_key, SECKEYBLOBSIZE);
	if (__paes_set_key(ctx)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}
	return 0;
}