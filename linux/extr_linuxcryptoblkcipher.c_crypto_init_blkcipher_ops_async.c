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
struct ablkcipher_tfm {int /*<<< orphan*/  ivsize; int /*<<< orphan*/  base; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct ablkcipher_tfm crt_ablkcipher; } ;
struct blkcipher_alg {int /*<<< orphan*/  ivsize; } ;
struct TYPE_2__ {struct blkcipher_alg cra_blkcipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_ablkcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  async_decrypt ; 
 int /*<<< orphan*/  async_encrypt ; 
 int /*<<< orphan*/  async_setkey ; 

__attribute__((used)) static int crypto_init_blkcipher_ops_async(struct crypto_tfm *tfm)
{
	struct ablkcipher_tfm *crt = &tfm->crt_ablkcipher;
	struct blkcipher_alg *alg = &tfm->__crt_alg->cra_blkcipher;

	crt->setkey = async_setkey;
	crt->encrypt = async_encrypt;
	crt->decrypt = async_decrypt;
	crt->base = __crypto_ablkcipher_cast(tfm);
	crt->ivsize = alg->ivsize;

	return 0;
}