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
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int mtd_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpddr2_nvm_remove(struct platform_device *pdev)
{
	return mtd_device_unregister(dev_get_drvdata(&pdev->dev));
}