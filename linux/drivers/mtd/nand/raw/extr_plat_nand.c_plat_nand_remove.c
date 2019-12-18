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
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct platform_device*) ;} ;
struct platform_nand_data {TYPE_1__ ctrl; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct plat_nand_data {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 struct platform_nand_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct plat_nand_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

__attribute__((used)) static int plat_nand_remove(struct platform_device *pdev)
{
	struct plat_nand_data *data = platform_get_drvdata(pdev);
	struct platform_nand_data *pdata = dev_get_platdata(&pdev->dev);

	nand_release(&data->chip);
	if (pdata->ctrl.remove)
		pdata->ctrl.remove(pdev);

	return 0;
}