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
struct wm831x_on {int /*<<< orphan*/  work; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct wm831x_on*) ; 
 struct wm831x_on* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_on_remove(struct platform_device *pdev)
{
	struct wm831x_on *wm831x_on = platform_get_drvdata(pdev);
	int irq = platform_get_irq(pdev, 0);

	free_irq(irq, wm831x_on);
	cancel_delayed_work_sync(&wm831x_on->work);

	return 0;
}