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
struct usbtll_omap {int nch; int /*<<< orphan*/ * ch_clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct usbtll_omap* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tll_dev ; 
 int /*<<< orphan*/  tll_lock ; 

__attribute__((used)) static int usbtll_omap_remove(struct platform_device *pdev)
{
	struct usbtll_omap *tll = platform_get_drvdata(pdev);
	int i;

	spin_lock(&tll_lock);
	tll_dev = NULL;
	spin_unlock(&tll_lock);

	for (i = 0; i < tll->nch; i++) {
		if (!IS_ERR(tll->ch_clk[i])) {
			clk_unprepare(tll->ch_clk[i]);
			clk_put(tll->ch_clk[i]);
		}
	}

	pm_runtime_disable(&pdev->dev);
	return 0;
}