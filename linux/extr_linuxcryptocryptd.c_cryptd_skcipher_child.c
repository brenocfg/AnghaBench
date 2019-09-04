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
struct crypto_skcipher {int dummy; } ;
struct cryptd_skcipher_ctx {struct crypto_skcipher* child; } ;
struct cryptd_skcipher {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct cryptd_skcipher_ctx* crypto_skcipher_ctx (int /*<<< orphan*/ *) ; 

struct crypto_skcipher *cryptd_skcipher_child(struct cryptd_skcipher *tfm)
{
	struct cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(&tfm->base);

	return ctx->child;
}