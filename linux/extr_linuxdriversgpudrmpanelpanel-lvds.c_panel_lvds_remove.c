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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct panel_lvds {TYPE_1__* backlight; int /*<<< orphan*/  panel; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct panel_lvds* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_lvds_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_lvds_remove(struct platform_device *pdev)
{
	struct panel_lvds *lvds = dev_get_drvdata(&pdev->dev);

	drm_panel_remove(&lvds->panel);

	panel_lvds_disable(&lvds->panel);

	if (lvds->backlight)
		put_device(&lvds->backlight->dev);

	return 0;
}