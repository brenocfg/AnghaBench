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
struct platform_device {int dummy; } ;
struct pic32_rng {int /*<<< orphan*/  clk; scalar_t__ base; int /*<<< orphan*/  rng; } ;

/* Variables and functions */
 scalar_t__ RNGCON ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 struct pic32_rng* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pic32_rng_remove(struct platform_device *pdev)
{
	struct pic32_rng *rng = platform_get_drvdata(pdev);

	hwrng_unregister(&rng->rng);
	writel(0, rng->base + RNGCON);
	clk_disable_unprepare(rng->clk);
	return 0;
}