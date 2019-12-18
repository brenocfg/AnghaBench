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
typedef  int u32 ;
struct mpc_i2c {int real_clk; scalar_t__ base; } ;

/* Variables and functions */
 int CCR_MEN ; 
 int CCR_MSTA ; 
 int CCR_MTX ; 
 scalar_t__ MPC_I2C_DR ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeccr (struct mpc_i2c*,int) ; 

__attribute__((used)) static void mpc_i2c_fixup(struct mpc_i2c *i2c)
{
	int k;
	u32 delay_val = 1000000 / i2c->real_clk + 1;

	if (delay_val < 2)
		delay_val = 2;

	for (k = 9; k; k--) {
		writeccr(i2c, 0);
		writeccr(i2c, CCR_MSTA | CCR_MTX | CCR_MEN);
		readb(i2c->base + MPC_I2C_DR);
		writeccr(i2c, CCR_MEN);
		udelay(delay_val << 1);
	}
}