#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xilinxfb_platform_data {int rotate_screen; scalar_t__ yvirt; scalar_t__ xvirt; scalar_t__ yres; scalar_t__ xres; scalar_t__ screen_height_mm; scalar_t__ screen_width_mm; } ;
struct xilinxfb_drvdata {int /*<<< orphan*/  dcr_host; int /*<<< orphan*/  dcr_len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ACCESS_FLAG ; 
 int /*<<< orphan*/  DCR_MAP_OK (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcr_map (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcr_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcr_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct xilinxfb_drvdata*) ; 
 struct xilinxfb_drvdata* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 struct xilinxfb_platform_data xilinx_fb_default_pdata ; 
 int xilinxfb_assign (struct platform_device*,struct xilinxfb_drvdata*,struct xilinxfb_platform_data*) ; 

__attribute__((used)) static int xilinxfb_of_probe(struct platform_device *pdev)
{
	const u32 *prop;
	u32 tft_access = 0;
	struct xilinxfb_platform_data pdata;
	int size;
	struct xilinxfb_drvdata *drvdata;

	/* Copy with the default pdata (not a ptr reference!) */
	pdata = xilinx_fb_default_pdata;

	/* Allocate the driver data region */
	drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	/*
	 * To check whether the core is connected directly to DCR or BUS
	 * interface and initialize the tft_access accordingly.
	 */
	of_property_read_u32(pdev->dev.of_node, "xlnx,dcr-splb-slave-if",
			     &tft_access);

	/*
	 * Fill the resource structure if its direct BUS interface
	 * otherwise fill the dcr_host structure.
	 */
	if (tft_access)
		drvdata->flags |= BUS_ACCESS_FLAG;
#ifdef CONFIG_PPC_DCR
	else {
		int start;

		start = dcr_resource_start(pdev->dev.of_node, 0);
		drvdata->dcr_len = dcr_resource_len(pdev->dev.of_node, 0);
		drvdata->dcr_host = dcr_map(pdev->dev.of_node, start, drvdata->dcr_len);
		if (!DCR_MAP_OK(drvdata->dcr_host)) {
			dev_err(&pdev->dev, "invalid DCR address\n");
			return -ENODEV;
		}
	}
#endif

	prop = of_get_property(pdev->dev.of_node, "phys-size", &size);
	if ((prop) && (size >= sizeof(u32) * 2)) {
		pdata.screen_width_mm = prop[0];
		pdata.screen_height_mm = prop[1];
	}

	prop = of_get_property(pdev->dev.of_node, "resolution", &size);
	if ((prop) && (size >= sizeof(u32) * 2)) {
		pdata.xres = prop[0];
		pdata.yres = prop[1];
	}

	prop = of_get_property(pdev->dev.of_node, "virtual-resolution", &size);
	if ((prop) && (size >= sizeof(u32) * 2)) {
		pdata.xvirt = prop[0];
		pdata.yvirt = prop[1];
	}

	if (of_find_property(pdev->dev.of_node, "rotate-display", NULL))
		pdata.rotate_screen = 1;

	dev_set_drvdata(&pdev->dev, drvdata);
	return xilinxfb_assign(pdev, drvdata, &pdata);
}