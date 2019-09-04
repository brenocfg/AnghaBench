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
struct seiko_panel {int /*<<< orphan*/  base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct seiko_panel* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seiko_panel_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seiko_panel_shutdown(struct platform_device *pdev)
{
	struct seiko_panel *panel = dev_get_drvdata(&pdev->dev);

	seiko_panel_disable(&panel->base);
}