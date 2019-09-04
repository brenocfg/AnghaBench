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
struct skcipher_request {int dummy; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct crypto_skcipher {int dummy; } ;
struct ablkcipher_alg {int /*<<< orphan*/  encrypt; } ;
struct TYPE_2__ {struct ablkcipher_alg cra_ablkcipher; } ;

/* Variables and functions */
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 int skcipher_crypt_ablkcipher (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skcipher_encrypt_ablkcipher(struct skcipher_request *req)
{
	struct crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_skcipher_tfm(skcipher);
	struct ablkcipher_alg *alg = &tfm->__crt_alg->cra_ablkcipher;

	return skcipher_crypt_ablkcipher(req, alg->encrypt);
}