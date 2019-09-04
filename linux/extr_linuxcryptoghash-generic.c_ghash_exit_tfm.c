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
struct ghash_ctx {scalar_t__ gf128; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct ghash_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  gf128mul_free_4k (scalar_t__) ; 

__attribute__((used)) static void ghash_exit_tfm(struct crypto_tfm *tfm)
{
	struct ghash_ctx *ctx = crypto_tfm_ctx(tfm);
	if (ctx->gf128)
		gf128mul_free_4k(ctx->gf128);
}