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
struct mtk_i2c {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ REG_SM0CFG2_REG ; 
 scalar_t__ REG_SM0CTL0_REG ; 
 scalar_t__ REG_SM0CTL1_REG ; 
 scalar_t__ REG_SM0D0_REG ; 
 scalar_t__ REG_SM0D1_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static void mtk_i2c_dump_reg(struct mtk_i2c *i2c)
{
	dev_dbg(i2c->dev,
		"SM0CFG2 %08x, SM0CTL0 %08x, SM0CTL1 %08x, SM0D0 %08x, SM0D1 %08x\n",
		ioread32(i2c->base + REG_SM0CFG2_REG),
		ioread32(i2c->base + REG_SM0CTL0_REG),
		ioread32(i2c->base + REG_SM0CTL1_REG),
		ioread32(i2c->base + REG_SM0D0_REG),
		ioread32(i2c->base + REG_SM0D1_REG));
}