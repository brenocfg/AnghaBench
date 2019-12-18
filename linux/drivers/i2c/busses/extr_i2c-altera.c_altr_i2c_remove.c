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
struct platform_device {int dummy; } ;
struct altr_i2c_dev {int /*<<< orphan*/  adapter; int /*<<< orphan*/  i2c_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct altr_i2c_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int altr_i2c_remove(struct platform_device *pdev)
{
	struct altr_i2c_dev *idev = platform_get_drvdata(pdev);

	clk_disable_unprepare(idev->i2c_clk);
	i2c_del_adapter(&idev->adapter);

	return 0;
}