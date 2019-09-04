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
typedef  unsigned char u32 ;
struct sirfsoc_i2c {int /*<<< orphan*/  cmd_ptr; scalar_t__ base; scalar_t__ last; } ;
struct i2c_msg {scalar_t__ len; int flags; } ;

/* Variables and functions */
 int I2C_M_REV_DIR_ADDR ; 
 scalar_t__ SIRFSOC_I2C_CMD (int /*<<< orphan*/ ) ; 
 unsigned char SIRFSOC_I2C_CMD_RP (int /*<<< orphan*/ ) ; 
 unsigned char SIRFSOC_I2C_START ; 
 unsigned char SIRFSOC_I2C_STOP ; 
 unsigned char SIRFSOC_I2C_WRITE ; 
 unsigned char i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

__attribute__((used)) static void i2c_sirfsoc_set_address(struct sirfsoc_i2c *siic,
	struct i2c_msg *msg)
{
	unsigned char addr;
	u32 regval = SIRFSOC_I2C_START | SIRFSOC_I2C_CMD_RP(0) | SIRFSOC_I2C_WRITE;

	/* no data and last message -> add STOP */
	if (siic->last && (msg->len == 0))
		regval |= SIRFSOC_I2C_STOP;

	writel(regval, siic->base + SIRFSOC_I2C_CMD(siic->cmd_ptr++));

	addr = i2c_8bit_addr_from_msg(msg);

	/* Reverse direction bit */
	if (msg->flags & I2C_M_REV_DIR_ADDR)
		addr ^= 1;

	writel(addr, siic->base + SIRFSOC_I2C_CMD(siic->cmd_ptr++));
}