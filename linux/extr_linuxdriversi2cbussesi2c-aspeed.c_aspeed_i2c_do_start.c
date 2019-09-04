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
typedef  int u8 ;
typedef  int u32 ;
struct i2c_msg {int flags; int len; } ;
struct aspeed_i2c_bus {size_t msgs_index; scalar_t__ base; scalar_t__ buf_index; int /*<<< orphan*/  master_state; struct i2c_msg* msgs; } ;

/* Variables and functions */
 int ASPEED_I2CD_M_RX_CMD ; 
 int ASPEED_I2CD_M_START_CMD ; 
 int ASPEED_I2CD_M_S_RX_CMD_LAST ; 
 int ASPEED_I2CD_M_TX_CMD ; 
 scalar_t__ ASPEED_I2C_BYTE_BUF_REG ; 
 scalar_t__ ASPEED_I2C_CMD_REG ; 
 int /*<<< orphan*/  ASPEED_I2C_MASTER_START ; 
 int I2C_M_RD ; 
 int I2C_M_RECV_LEN ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aspeed_i2c_do_start(struct aspeed_i2c_bus *bus)
{
	u32 command = ASPEED_I2CD_M_START_CMD | ASPEED_I2CD_M_TX_CMD;
	struct i2c_msg *msg = &bus->msgs[bus->msgs_index];
	u8 slave_addr = i2c_8bit_addr_from_msg(msg);

	bus->master_state = ASPEED_I2C_MASTER_START;
	bus->buf_index = 0;

	if (msg->flags & I2C_M_RD) {
		command |= ASPEED_I2CD_M_RX_CMD;
		/* Need to let the hardware know to NACK after RX. */
		if (msg->len == 1 && !(msg->flags & I2C_M_RECV_LEN))
			command |= ASPEED_I2CD_M_S_RX_CMD_LAST;
	}

	writel(slave_addr, bus->base + ASPEED_I2C_BYTE_BUF_REG);
	writel(command, bus->base + ASPEED_I2C_CMD_REG);
}