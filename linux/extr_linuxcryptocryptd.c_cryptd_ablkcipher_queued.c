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
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct cryptd_blkcipher_ctx* crypto_ablkcipher_ctx (int /*<<< orphan*/ *) ; 

bool cryptd_ablkcipher_queued(struct cryptd_ablkcipher *tfm)
{
	struct cryptd_blkcipher_ctx *ctx = crypto_ablkcipher_ctx(&tfm->base);

	return atomic_read(&ctx->refcnt) - 1;
}