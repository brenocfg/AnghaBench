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
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct crypto_aead* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (struct crypto_aead*,int) ; 
 int crypto_aead_setkey (struct crypto_aead*,char*,int) ; 
 struct crypto_aead* crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (struct crypto_aead*) ; 

__attribute__((used)) static struct crypto_aead *macsec_alloc_tfm(char *key, int key_len, int icv_len)
{
	struct crypto_aead *tfm;
	int ret;

	tfm = crypto_alloc_aead("gcm(aes)", 0, 0);

	if (IS_ERR(tfm))
		return tfm;

	ret = crypto_aead_setkey(tfm, key, key_len);
	if (ret < 0)
		goto fail;

	ret = crypto_aead_setauthsize(tfm, icv_len);
	if (ret < 0)
		goto fail;

	return tfm;
fail:
	crypto_free_aead(tfm);
	return ERR_PTR(ret);
}