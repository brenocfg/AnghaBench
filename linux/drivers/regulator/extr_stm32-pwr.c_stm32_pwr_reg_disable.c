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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_pwr_reg {scalar_t__ base; } ;
struct regulator_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 scalar_t__ REG_PWR_CR3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stm32_pwr_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct regulator_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stm32_pwr_reg_is_ready ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stm32_pwr_reg_disable(struct regulator_dev *rdev)
{
	struct stm32_pwr_reg *priv = rdev_get_drvdata(rdev);
	int ret;
	u32 val;

	val = readl_relaxed(priv->base + REG_PWR_CR3);
	val &= ~rdev->desc->enable_mask;
	writel_relaxed(val, priv->base + REG_PWR_CR3);

	/* use an arbitrary timeout of 20ms */
	ret = readx_poll_timeout(stm32_pwr_reg_is_ready, rdev, val, !val,
				 100, 20 * 1000);
	if (ret)
		dev_err(&rdev->dev, "regulator disable timed out!\n");

	return ret;
}