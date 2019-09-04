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
struct s390_aes_ctx {unsigned long fc; unsigned int key_len; int /*<<< orphan*/  key; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 unsigned long CPACF_KM_AES_128 ; 
 unsigned long CPACF_KM_AES_192 ; 
 unsigned long CPACF_KM_AES_256 ; 
 scalar_t__ cpacf_test_func (int /*<<< orphan*/ *,unsigned long) ; 
 struct s390_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  km_functions ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int setkey_fallback_blk (struct crypto_tfm*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int ecb_aes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			   unsigned int key_len)
{
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);
	unsigned long fc;

	/* Pick the correct function code based on the key length */
	fc = (key_len == 16) ? CPACF_KM_AES_128 :
	     (key_len == 24) ? CPACF_KM_AES_192 :
	     (key_len == 32) ? CPACF_KM_AES_256 : 0;

	/* Check if the function code is available */
	sctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;
	if (!sctx->fc)
		return setkey_fallback_blk(tfm, in_key, key_len);

	sctx->key_len = key_len;
	memcpy(sctx->key, in_key, key_len);
	return 0;
}