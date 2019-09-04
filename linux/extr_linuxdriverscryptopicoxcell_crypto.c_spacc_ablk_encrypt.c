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
struct spacc_alg {int /*<<< orphan*/  type; } ;
struct crypto_tfm {int /*<<< orphan*/  __crt_alg; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int spacc_ablk_setup (struct ablkcipher_request*,int /*<<< orphan*/ ,int) ; 
 struct spacc_alg* to_spacc_alg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spacc_ablk_encrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct spacc_alg *alg = to_spacc_alg(tfm->__crt_alg);

	return spacc_ablk_setup(req, alg->type, 1);
}