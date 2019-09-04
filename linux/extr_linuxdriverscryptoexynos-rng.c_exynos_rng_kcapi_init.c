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
struct exynos_rng_ctx {int /*<<< orphan*/  rng; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct exynos_rng_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  exynos_rng_dev ; 

__attribute__((used)) static int exynos_rng_kcapi_init(struct crypto_tfm *tfm)
{
	struct exynos_rng_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->rng = exynos_rng_dev;

	return 0;
}