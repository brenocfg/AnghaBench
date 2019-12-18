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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fbdev_panel ; 
 struct platform_device* fbdev_pdev ; 
 int /*<<< orphan*/  omapdss_device ; 
 int /*<<< orphan*/  omapfb_do_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omapfb_probe(struct platform_device *pdev)
{
	int r;

	BUG_ON(fbdev_pdev != NULL);

	r = platform_device_register(&omapdss_device);
	if (r) {
		dev_err(&pdev->dev, "can't register omapdss device\n");
		return r;
	}

	/* Delay actual initialization until the LCD is registered */
	fbdev_pdev = pdev;
	if (fbdev_panel != NULL)
		omapfb_do_probe(fbdev_pdev, fbdev_panel);
	return 0;
}