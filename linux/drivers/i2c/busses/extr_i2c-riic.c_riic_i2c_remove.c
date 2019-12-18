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
struct riic_dev {int /*<<< orphan*/  adapter; scalar_t__ base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ RIIC_ICIER ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct riic_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int riic_i2c_remove(struct platform_device *pdev)
{
	struct riic_dev *riic = platform_get_drvdata(pdev);

	pm_runtime_get_sync(&pdev->dev);
	writeb(0, riic->base + RIIC_ICIER);
	pm_runtime_put(&pdev->dev);
	i2c_del_adapter(&riic->adapter);
	pm_runtime_disable(&pdev->dev);

	return 0;
}