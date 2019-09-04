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
struct crypto_blkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_blkcipher (struct crypto_blkcipher*) ; 
 struct crypto_blkcipher** crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void crypto_exit_skcipher_ops_blkcipher(struct crypto_tfm *tfm)
{
	struct crypto_blkcipher **ctx = crypto_tfm_ctx(tfm);

	crypto_free_blkcipher(*ctx);
}