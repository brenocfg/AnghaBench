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
struct i2c_adapter {int dummy; } ;
struct zd1301_demod_dev {struct i2c_adapter adapter; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct zd1301_demod_dev* platform_get_drvdata (struct platform_device*) ; 

struct i2c_adapter *zd1301_demod_get_i2c_adapter(struct platform_device *pdev)
{
	struct zd1301_demod_dev *dev = platform_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	return &dev->adapter;
}