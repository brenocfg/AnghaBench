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
struct ili9322 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILI9322_POW_CTRL ; 
 int /*<<< orphan*/  ILI9322_POW_CTRL_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ili9322* panel_to_ili9322 (struct drm_panel*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ili9322_enable(struct drm_panel *panel)
{
	struct ili9322 *ili = panel_to_ili9322(panel);
	int ret;

	ret = regmap_write(ili->regmap, ILI9322_POW_CTRL,
			   ILI9322_POW_CTRL_DEFAULT);
	if (ret) {
		dev_err(ili->dev, "unable to enable panel\n");
		return ret;
	}

	return 0;
}