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
struct meson_audio_arb_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct meson_audio_arb_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_audio_arb_remove(struct platform_device *pdev)
{
	struct meson_audio_arb_data *arb = platform_get_drvdata(pdev);

	/* Disable all access */
	spin_lock(&arb->lock);
	writel(0, arb->regs);
	spin_unlock(&arb->lock);

	clk_disable_unprepare(arb->clk);

	return 0;
}