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
struct hwrng {int dummy; } ;
struct bcm2835_rng_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RNG_CTRL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rng_writel (struct bcm2835_rng_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm2835_rng_priv* to_rng_priv (struct hwrng*) ; 

__attribute__((used)) static void bcm2835_rng_cleanup(struct hwrng *rng)
{
	struct bcm2835_rng_priv *priv = to_rng_priv(rng);

	/* disable rng hardware */
	rng_writel(priv, 0, RNG_CTRL);

	if (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);
}