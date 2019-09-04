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
struct cryptd_blkcipher_ctx {int /*<<< orphan*/  refcnt; } ;
struct cryptd_ablkcipher {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct cryptd_blkcipher_ctx* crypto_ablkcipher_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_ablkcipher (int /*<<< orphan*/ *) ; 

void cryptd_free_ablkcipher(struct cryptd_ablkcipher *tfm)
{
	struct cryptd_blkcipher_ctx *ctx = crypto_ablkcipher_ctx(&tfm->base);

	if (atomic_dec_and_test(&ctx->refcnt))
		crypto_free_ablkcipher(&tfm->base);
}