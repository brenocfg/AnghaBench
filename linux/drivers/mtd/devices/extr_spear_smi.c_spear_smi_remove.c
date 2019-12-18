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
struct spear_snor_flash {int /*<<< orphan*/  mtd; } ;
struct spear_smi {int num_flashes; int /*<<< orphan*/  clk; struct spear_snor_flash** flash; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct spear_smi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int spear_smi_remove(struct platform_device *pdev)
{
	struct spear_smi *dev;
	struct spear_snor_flash *flash;
	int ret, i;

	dev = platform_get_drvdata(pdev);
	if (!dev) {
		dev_err(&pdev->dev, "dev is null\n");
		return -ENODEV;
	}

	/* clean up for all nor flash */
	for (i = 0; i < dev->num_flashes; i++) {
		flash = dev->flash[i];
		if (!flash)
			continue;

		/* clean up mtd stuff */
		ret = mtd_device_unregister(&flash->mtd);
		if (ret)
			dev_err(&pdev->dev, "error removing mtd\n");
	}

	clk_disable_unprepare(dev->clk);

	return 0;
}