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
typedef  int u32 ;
struct hwrng {scalar_t__ priv; } ;
struct exynos_trng_dev {scalar_t__ mem; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ EXYNOS_TRNG_CLKDIV ; 
 int EXYNOS_TRNG_CLOCK_RATE ; 
 scalar_t__ EXYNOS_TRNG_CTRL ; 
 int EXYNOS_TRNG_CTRL_RNGEN ; 
 scalar_t__ EXYNOS_TRNG_POST_CTRL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int exynos_trng_init(struct hwrng *rng)
{
	struct exynos_trng_dev *trng = (struct exynos_trng_dev *)rng->priv;
	unsigned long sss_rate;
	u32 val;

	sss_rate = clk_get_rate(trng->clk);

	/*
	 * For most TRNG circuits the clock frequency of under 500 kHz
	 * is safe.
	 */
	val = sss_rate / (EXYNOS_TRNG_CLOCK_RATE * 2);
	if (val > 0x7fff) {
		dev_err(trng->dev, "clock divider too large: %d", val);
		return -ERANGE;
	}
	val = val << 1;
	writel_relaxed(val, trng->mem + EXYNOS_TRNG_CLKDIV);

	/* Enable the generator. */
	val = EXYNOS_TRNG_CTRL_RNGEN;
	writel_relaxed(val, trng->mem + EXYNOS_TRNG_CTRL);

	/*
	 * Disable post-processing. /dev/hwrng is supposed to deliver
	 * unprocessed data.
	 */
	writel_relaxed(0, trng->mem + EXYNOS_TRNG_POST_CTRL);

	return 0;
}