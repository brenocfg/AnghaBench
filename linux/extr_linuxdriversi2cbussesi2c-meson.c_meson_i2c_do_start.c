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
struct meson_i2c {scalar_t__ regs; } ;
struct i2c_msg {int flags; int addr; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 scalar_t__ REG_SLAVE_ADDR ; 
 int TOKEN_SLAVE_ADDR_READ ; 
 int TOKEN_SLAVE_ADDR_WRITE ; 
 int TOKEN_START ; 
 int /*<<< orphan*/  meson_i2c_add_token (struct meson_i2c*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_i2c_do_start(struct meson_i2c *i2c, struct i2c_msg *msg)
{
	int token;

	token = (msg->flags & I2C_M_RD) ? TOKEN_SLAVE_ADDR_READ :
		TOKEN_SLAVE_ADDR_WRITE;

	writel(msg->addr << 1, i2c->regs + REG_SLAVE_ADDR);
	meson_i2c_add_token(i2c, TOKEN_START);
	meson_i2c_add_token(i2c, token);
}