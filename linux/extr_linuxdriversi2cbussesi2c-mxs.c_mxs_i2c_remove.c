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
struct mxs_i2c_dev {scalar_t__ regs; scalar_t__ dmach; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ MXS_I2C_CTRL0_SET ; 
 int /*<<< orphan*/  MXS_I2C_CTRL0_SFTRST ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct mxs_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mxs_i2c_remove(struct platform_device *pdev)
{
	struct mxs_i2c_dev *i2c = platform_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adapter);

	if (i2c->dmach)
		dma_release_channel(i2c->dmach);

	writel(MXS_I2C_CTRL0_SFTRST, i2c->regs + MXS_I2C_CTRL0_SET);

	return 0;
}