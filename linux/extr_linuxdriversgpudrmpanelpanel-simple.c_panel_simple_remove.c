#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panel_simple {TYPE_1__* backlight; TYPE_2__* ddc; int /*<<< orphan*/  base; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct panel_simple* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_simple_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_simple_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_simple_remove(struct device *dev)
{
	struct panel_simple *panel = dev_get_drvdata(dev);

	drm_panel_remove(&panel->base);

	panel_simple_disable(&panel->base);
	panel_simple_unprepare(&panel->base);

	if (panel->ddc)
		put_device(&panel->ddc->dev);

	if (panel->backlight)
		put_device(&panel->backlight->dev);

	return 0;
}