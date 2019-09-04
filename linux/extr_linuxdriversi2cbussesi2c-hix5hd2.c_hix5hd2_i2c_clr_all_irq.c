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
struct hix5hd2_i2c_priv {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HIX5I2C_ICR ; 
 int /*<<< orphan*/  I2C_CLEAR_ALL ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hix5hd2_i2c_clr_all_irq(struct hix5hd2_i2c_priv *priv)
{
	writel_relaxed(I2C_CLEAR_ALL, priv->regs + HIX5I2C_ICR);
}