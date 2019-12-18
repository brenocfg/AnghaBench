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
struct crypto_shash {int dummy; } ;
struct alg_spec {int /*<<< orphan*/  key_size; scalar_t__ key; scalar_t__ alg_string; } ;

/* Variables and functions */
 int CRYPTO_TFM_NEED_KEY ; 
 int ENOKEY ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_shash_get_flags (struct crypto_shash*) ; 
 int crypto_shash_setkey (struct crypto_shash*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_mac(struct crypto_shash **hash, struct alg_spec *a, char **error,
		   char *error_alg, char *error_key)
{
	int r;

	if (a->alg_string) {
		*hash = crypto_alloc_shash(a->alg_string, 0, 0);
		if (IS_ERR(*hash)) {
			*error = error_alg;
			r = PTR_ERR(*hash);
			*hash = NULL;
			return r;
		}

		if (a->key) {
			r = crypto_shash_setkey(*hash, a->key, a->key_size);
			if (r) {
				*error = error_key;
				return r;
			}
		} else if (crypto_shash_get_flags(*hash) & CRYPTO_TFM_NEED_KEY) {
			*error = error_key;
			return -ENOKEY;
		}
	}

	return 0;
}