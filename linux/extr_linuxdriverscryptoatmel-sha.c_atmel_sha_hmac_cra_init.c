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
struct crypto_tfm {int dummy; } ;
struct atmel_sha_reqctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct atmel_sha_hmac_ctx {int /*<<< orphan*/  hkey; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  atmel_sha_hmac_key_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmel_sha_hmac_start ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 
 struct atmel_sha_hmac_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int atmel_sha_hmac_cra_init(struct crypto_tfm *tfm)
{
	struct atmel_sha_hmac_ctx *hmac = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct atmel_sha_reqctx));
	hmac->base.start = atmel_sha_hmac_start;
	atmel_sha_hmac_key_init(&hmac->hkey);

	return 0;
}