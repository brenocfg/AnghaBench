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
typedef  int /*<<< orphan*/  u32 ;
struct img_i2c {int t_halt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_CONTROL_REG ; 
 int /*<<< orphan*/  SCB_CONTROL_TRANSACTION_HALT ; 
 int /*<<< orphan*/  img_i2c_readl (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_i2c_transaction_halt(struct img_i2c *i2c, bool t_halt)
{
	u32 val;

	if (i2c->t_halt == t_halt)
		return;
	i2c->t_halt = t_halt;
	val = img_i2c_readl(i2c, SCB_CONTROL_REG);
	if (t_halt)
		val |= SCB_CONTROL_TRANSACTION_HALT;
	else
		val &= ~SCB_CONTROL_TRANSACTION_HALT;
	img_i2c_writel(i2c, SCB_CONTROL_REG, val);
}