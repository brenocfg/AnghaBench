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
typedef  int /*<<< orphan*/  u16 ;
struct mtk_i2c {TYPE_1__* dev_comp; scalar_t__ base; } ;
typedef  enum I2C_REGS_OFFSET { ____Placeholder_I2C_REGS_OFFSET } I2C_REGS_OFFSET ;
struct TYPE_2__ {scalar_t__* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static u16 mtk_i2c_readw(struct mtk_i2c *i2c, enum I2C_REGS_OFFSET reg)
{
	return readw(i2c->base + i2c->dev_comp->regs[reg]);
}