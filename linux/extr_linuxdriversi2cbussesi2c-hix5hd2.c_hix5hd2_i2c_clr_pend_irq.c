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
struct hix5hd2_i2c_priv {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HIX5I2C_ICR ; 
 scalar_t__ HIX5I2C_SR ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 hix5hd2_i2c_clr_pend_irq(struct hix5hd2_i2c_priv *priv)
{
	u32 val = readl_relaxed(priv->regs + HIX5I2C_SR);

	writel_relaxed(val, priv->regs + HIX5I2C_ICR);

	return val;
}