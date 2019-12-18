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
struct ls037v7dw01_panel {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ *) ; 
 struct ls037v7dw01_panel* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ls037v7dw01_remove(struct platform_device *pdev)
{
	struct ls037v7dw01_panel *lcd = platform_get_drvdata(pdev);

	drm_panel_remove(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	return 0;
}