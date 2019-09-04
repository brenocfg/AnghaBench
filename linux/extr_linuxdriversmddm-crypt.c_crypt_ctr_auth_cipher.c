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
struct crypto_ahash {int dummy; } ;
struct crypt_config {int /*<<< orphan*/  authenc_key; int /*<<< orphan*/  key_mac_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int PTR_ERR (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypt_authenckey_size (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_alloc_ahash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  strstarts (char*,char*) ; 

__attribute__((used)) static int crypt_ctr_auth_cipher(struct crypt_config *cc, char *cipher_api)
{
	char *start, *end, *mac_alg = NULL;
	struct crypto_ahash *mac;

	if (!strstarts(cipher_api, "authenc("))
		return 0;

	start = strchr(cipher_api, '(');
	end = strchr(cipher_api, ',');
	if (!start || !end || ++start > end)
		return -EINVAL;

	mac_alg = kzalloc(end - start + 1, GFP_KERNEL);
	if (!mac_alg)
		return -ENOMEM;
	strncpy(mac_alg, start, end - start);

	mac = crypto_alloc_ahash(mac_alg, 0, 0);
	kfree(mac_alg);

	if (IS_ERR(mac))
		return PTR_ERR(mac);

	cc->key_mac_size = crypto_ahash_digestsize(mac);
	crypto_free_ahash(mac);

	cc->authenc_key = kmalloc(crypt_authenckey_size(cc), GFP_KERNEL);
	if (!cc->authenc_key)
		return -ENOMEM;

	return 0;
}