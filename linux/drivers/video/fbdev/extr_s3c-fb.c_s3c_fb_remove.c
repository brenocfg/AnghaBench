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
struct TYPE_2__ {int /*<<< orphan*/  has_clksel; } ;
struct s3c_fb {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  lcd_clk; TYPE_1__ variant; scalar_t__* windows; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int S3C_FB_MAX_WIN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct s3c_fb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_fb_release_win (struct s3c_fb*,scalar_t__) ; 

__attribute__((used)) static int s3c_fb_remove(struct platform_device *pdev)
{
	struct s3c_fb *sfb = platform_get_drvdata(pdev);
	int win;

	pm_runtime_get_sync(sfb->dev);

	for (win = 0; win < S3C_FB_MAX_WIN; win++)
		if (sfb->windows[win])
			s3c_fb_release_win(sfb, sfb->windows[win]);

	if (!sfb->variant.has_clksel)
		clk_disable_unprepare(sfb->lcd_clk);

	clk_disable_unprepare(sfb->bus_clk);

	pm_runtime_put_sync(sfb->dev);
	pm_runtime_disable(sfb->dev);

	return 0;
}