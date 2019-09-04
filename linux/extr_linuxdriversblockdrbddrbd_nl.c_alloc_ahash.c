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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int NO_ERROR ; 
 struct crypto_ahash* crypto_alloc_ahash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alloc_ahash(struct crypto_ahash **tfm, char *tfm_name, int err_alg)
{
	if (!tfm_name[0])
		return NO_ERROR;

	*tfm = crypto_alloc_ahash(tfm_name, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(*tfm)) {
		*tfm = NULL;
		return err_alg;
	}

	return NO_ERROR;
}