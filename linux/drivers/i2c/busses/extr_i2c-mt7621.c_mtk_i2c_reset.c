#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct mtk_i2c {int clk_div; scalar_t__ base; int /*<<< orphan*/  dev; TYPE_2__ adap; } ;

/* Variables and functions */
 scalar_t__ REG_SM0CFG2_REG ; 
 scalar_t__ REG_SM0CTL0_REG ; 
 int SM0CTL0_CLK_DIV_MASK ; 
 int SM0CTL0_EN ; 
 int SM0CTL0_SCL_STRETCH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int device_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void mtk_i2c_reset(struct mtk_i2c *i2c)
{
	int ret;

	ret = device_reset(i2c->adap.dev.parent);
	if (ret)
		dev_err(i2c->dev, "I2C reset failed!\n");

	/*
	 * Don't set SM0CTL0_ODRAIN as its bit meaning is inverted. To
	 * configure open-drain mode, this bit needs to be cleared.
	 */
	iowrite32(((i2c->clk_div << 16) & SM0CTL0_CLK_DIV_MASK) | SM0CTL0_EN |
		  SM0CTL0_SCL_STRETCH, i2c->base + REG_SM0CTL0_REG);
	iowrite32(0, i2c->base + REG_SM0CFG2_REG);
}