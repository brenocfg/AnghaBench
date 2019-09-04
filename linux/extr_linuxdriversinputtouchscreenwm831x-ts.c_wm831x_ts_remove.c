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
struct wm831x_ts {int /*<<< orphan*/  data_irq; int /*<<< orphan*/  pd_irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wm831x_ts*) ; 
 struct wm831x_ts* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int wm831x_ts_remove(struct platform_device *pdev)
{
	struct wm831x_ts *wm831x_ts = platform_get_drvdata(pdev);

	free_irq(wm831x_ts->pd_irq, wm831x_ts);
	free_irq(wm831x_ts->data_irq, wm831x_ts);

	return 0;
}