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
struct sec_alg_tfm_ctx {TYPE_1__* queue; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  softqueue; } ;

/* Variables and functions */
 struct sec_alg_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_alg_skcipher_exit (struct crypto_skcipher*) ; 

__attribute__((used)) static void sec_alg_skcipher_exit_with_queue(struct crypto_skcipher *tfm)
{
	struct sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);

	kfifo_free(&ctx->queue->softqueue);
	sec_alg_skcipher_exit(tfm);
}