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
struct dln2_i2c {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dln2_i2c_enable (struct dln2_i2c*,int) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct dln2_i2c* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dln2_i2c_remove(struct platform_device *pdev)
{
	struct dln2_i2c *dln2 = platform_get_drvdata(pdev);

	i2c_del_adapter(&dln2->adapter);
	dln2_i2c_enable(dln2, false);

	return 0;
}