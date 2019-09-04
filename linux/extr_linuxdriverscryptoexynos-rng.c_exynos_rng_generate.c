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
typedef  int /*<<< orphan*/  u8 ;
struct exynos_rng_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; } ;
struct exynos_rng_ctx {struct exynos_rng_dev* rng; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct exynos_rng_ctx* crypto_rng_ctx (struct crypto_rng*) ; 
 int exynos_rng_get_random (struct exynos_rng_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  exynos_rng_reseed (struct exynos_rng_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_rng_generate(struct crypto_rng *tfm,
			       const u8 *src, unsigned int slen,
			       u8 *dst, unsigned int dlen)
{
	struct exynos_rng_ctx *ctx = crypto_rng_ctx(tfm);
	struct exynos_rng_dev *rng = ctx->rng;
	unsigned int read = 0;
	int ret;

	ret = clk_prepare_enable(rng->clk);
	if (ret)
		return ret;

	mutex_lock(&rng->lock);
	do {
		ret = exynos_rng_get_random(rng, dst, dlen, &read);
		if (ret)
			break;

		dlen -= read;
		dst += read;

		exynos_rng_reseed(rng);
	} while (dlen > 0);
	mutex_unlock(&rng->lock);

	clk_disable_unprepare(rng->clk);

	return ret;
}