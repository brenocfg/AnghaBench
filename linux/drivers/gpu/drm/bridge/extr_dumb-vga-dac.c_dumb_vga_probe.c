#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  timings; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct dumb_vga {TYPE_3__ bridge; int /*<<< orphan*/ * ddc; int /*<<< orphan*/ * vdd; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct dumb_vga* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_3__*) ; 
 int /*<<< orphan*/  dumb_vga_bridge_funcs ; 
 int /*<<< orphan*/ * dumb_vga_retrieve_ddc (TYPE_1__*) ; 
 int /*<<< orphan*/  of_device_get_match_data (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dumb_vga*) ; 

__attribute__((used)) static int dumb_vga_probe(struct platform_device *pdev)
{
	struct dumb_vga *vga;

	vga = devm_kzalloc(&pdev->dev, sizeof(*vga), GFP_KERNEL);
	if (!vga)
		return -ENOMEM;
	platform_set_drvdata(pdev, vga);

	vga->vdd = devm_regulator_get_optional(&pdev->dev, "vdd");
	if (IS_ERR(vga->vdd)) {
		int ret = PTR_ERR(vga->vdd);
		if (ret == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		vga->vdd = NULL;
		dev_dbg(&pdev->dev, "No vdd regulator found: %d\n", ret);
	}

	vga->ddc = dumb_vga_retrieve_ddc(&pdev->dev);
	if (IS_ERR(vga->ddc)) {
		if (PTR_ERR(vga->ddc) == -ENODEV) {
			dev_dbg(&pdev->dev,
				"No i2c bus specified. Disabling EDID readout\n");
			vga->ddc = NULL;
		} else {
			dev_err(&pdev->dev, "Couldn't retrieve i2c bus\n");
			return PTR_ERR(vga->ddc);
		}
	}

	vga->bridge.funcs = &dumb_vga_bridge_funcs;
	vga->bridge.of_node = pdev->dev.of_node;
	vga->bridge.timings = of_device_get_match_data(&pdev->dev);

	drm_bridge_add(&vga->bridge);

	return 0;
}