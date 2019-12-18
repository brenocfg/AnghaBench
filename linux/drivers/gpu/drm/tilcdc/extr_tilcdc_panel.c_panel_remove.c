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
struct tilcdc_module {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct panel_module {int /*<<< orphan*/  info; int /*<<< orphan*/  timings; struct backlight_device* backlight; } ;
struct backlight_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct tilcdc_module* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_timings_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tilcdc_module_cleanup (struct tilcdc_module*) ; 
 struct panel_module* to_panel_module (struct tilcdc_module*) ; 

__attribute__((used)) static int panel_remove(struct platform_device *pdev)
{
	struct tilcdc_module *mod = dev_get_platdata(&pdev->dev);
	struct panel_module *panel_mod = to_panel_module(mod);
	struct backlight_device *backlight = panel_mod->backlight;

	if (backlight)
		put_device(&backlight->dev);

	display_timings_release(panel_mod->timings);

	tilcdc_module_cleanup(mod);
	kfree(panel_mod->info);

	return 0;
}