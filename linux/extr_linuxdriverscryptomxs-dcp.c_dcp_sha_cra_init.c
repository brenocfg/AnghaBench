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
struct dcp_sha_req_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dcp_sha_cra_init(struct crypto_tfm *tfm)
{
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct dcp_sha_req_ctx));
	return 0;
}