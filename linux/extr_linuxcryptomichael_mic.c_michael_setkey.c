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
struct michael_mic_ctx {void* r; void* l; } ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 struct michael_mic_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_set_flags (struct crypto_shash*,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int michael_setkey(struct crypto_shash *tfm, const u8 *key,
			  unsigned int keylen)
{
	struct michael_mic_ctx *mctx = crypto_shash_ctx(tfm);

	const __le32 *data = (const __le32 *)key;

	if (keylen != 8) {
		crypto_shash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	mctx->l = le32_to_cpu(data[0]);
	mctx->r = le32_to_cpu(data[1]);
	return 0;
}