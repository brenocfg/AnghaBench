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
typedef  scalar_t__ u32 ;
struct rk_crypto_info {scalar_t__ reg; int /*<<< orphan*/  async_req; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 scalar_t__ DES_BLOCK_SIZE ; 
 scalar_t__ RK_CRYPTO_AES_IV_0 ; 
 scalar_t__ RK_CRYPTO_TDES_IV_0 ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void rk_iv_copyback(struct rk_crypto_info *dev)
{
	struct ablkcipher_request *req =
		ablkcipher_request_cast(dev->async_req);
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	u32 ivsize = crypto_ablkcipher_ivsize(tfm);

	if (ivsize == DES_BLOCK_SIZE)
		memcpy_fromio(req->info, dev->reg + RK_CRYPTO_TDES_IV_0,
			      ivsize);
	else if (ivsize == AES_BLOCK_SIZE)
		memcpy_fromio(req->info, dev->reg + RK_CRYPTO_AES_IV_0, ivsize);
}