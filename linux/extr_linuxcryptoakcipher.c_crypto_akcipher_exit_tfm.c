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
struct crypto_tfm {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct akcipher_alg {int /*<<< orphan*/  (* exit ) (struct crypto_akcipher*) ;} ;

/* Variables and functions */
 struct crypto_akcipher* __crypto_akcipher_tfm (struct crypto_tfm*) ; 
 struct akcipher_alg* crypto_akcipher_alg (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  stub1 (struct crypto_akcipher*) ; 

__attribute__((used)) static void crypto_akcipher_exit_tfm(struct crypto_tfm *tfm)
{
	struct crypto_akcipher *akcipher = __crypto_akcipher_tfm(tfm);
	struct akcipher_alg *alg = crypto_akcipher_alg(akcipher);

	alg->exit(akcipher);
}