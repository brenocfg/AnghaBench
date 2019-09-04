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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct camellia_ctx {unsigned int key_length; int /*<<< orphan*/  key_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  camellia_setup128 (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camellia_setup192 (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camellia_setup256 (unsigned char const*,int /*<<< orphan*/ ) ; 
 struct camellia_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int
camellia_set_key(struct crypto_tfm *tfm, const u8 *in_key,
		 unsigned int key_len)
{
	struct camellia_ctx *cctx = crypto_tfm_ctx(tfm);
	const unsigned char *key = (const unsigned char *)in_key;
	u32 *flags = &tfm->crt_flags;

	if (key_len != 16 && key_len != 24 && key_len != 32) {
		*flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	cctx->key_length = key_len;

	switch (key_len) {
	case 16:
		camellia_setup128(key, cctx->key_table);
		break;
	case 24:
		camellia_setup192(key, cctx->key_table);
		break;
	case 32:
		camellia_setup256(key, cctx->key_table);
		break;
	}

	return 0;
}