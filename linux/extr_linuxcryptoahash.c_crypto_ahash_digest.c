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
struct crypto_ahash {int /*<<< orphan*/  digest; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_NEED_KEY ; 
 int ENOKEY ; 
 int crypto_ahash_get_flags (struct crypto_ahash*) ; 
 int crypto_ahash_op (struct ahash_request*,int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 

int crypto_ahash_digest(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);

	if (crypto_ahash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		return -ENOKEY;

	return crypto_ahash_op(req, tfm->digest);
}