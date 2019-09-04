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
struct rk3x_i2c {int addr; int busy; scalar_t__ error; scalar_t__ processed; int /*<<< orphan*/  state; struct i2c_msg* msg; void* mode; int /*<<< orphan*/  dev; } ;
struct i2c_msg {int addr; int len; int flags; int* buf; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 void* REG_CON_MOD_REGISTER_TX ; 
 void* REG_CON_MOD_TX ; 
 int /*<<< orphan*/  REG_MRXADDR ; 
 int REG_MRXADDR_VALID (int) ; 
 int /*<<< orphan*/  REG_MRXRADDR ; 
 int /*<<< orphan*/  STATE_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3x_i2c_clean_ipd (struct rk3x_i2c*) ; 

__attribute__((used)) static int rk3x_i2c_setup(struct rk3x_i2c *i2c, struct i2c_msg *msgs, int num)
{
	u32 addr = (msgs[0].addr & 0x7f) << 1;
	int ret = 0;

	/*
	 * The I2C adapter can issue a small (len < 4) write packet before
	 * reading. This speeds up SMBus-style register reads.
	 * The MRXADDR/MRXRADDR hold the slave address and the slave register
	 * address in this case.
	 */

	if (num >= 2 && msgs[0].len < 4 &&
	    !(msgs[0].flags & I2C_M_RD) && (msgs[1].flags & I2C_M_RD)) {
		u32 reg_addr = 0;
		int i;

		dev_dbg(i2c->dev, "Combined write/read from addr 0x%x\n",
			addr >> 1);

		/* Fill MRXRADDR with the register address(es) */
		for (i = 0; i < msgs[0].len; ++i) {
			reg_addr |= msgs[0].buf[i] << (i * 8);
			reg_addr |= REG_MRXADDR_VALID(i);
		}

		/* msgs[0] is handled by hw. */
		i2c->msg = &msgs[1];

		i2c->mode = REG_CON_MOD_REGISTER_TX;

		i2c_writel(i2c, addr | REG_MRXADDR_VALID(0), REG_MRXADDR);
		i2c_writel(i2c, reg_addr, REG_MRXRADDR);

		ret = 2;
	} else {
		/*
		 * We'll have to do it the boring way and process the msgs
		 * one-by-one.
		 */

		if (msgs[0].flags & I2C_M_RD) {
			addr |= 1; /* set read bit */

			/*
			 * We have to transmit the slave addr first. Use
			 * MOD_REGISTER_TX for that purpose.
			 */
			i2c->mode = REG_CON_MOD_REGISTER_TX;
			i2c_writel(i2c, addr | REG_MRXADDR_VALID(0),
				   REG_MRXADDR);
			i2c_writel(i2c, 0, REG_MRXRADDR);
		} else {
			i2c->mode = REG_CON_MOD_TX;
		}

		i2c->msg = &msgs[0];

		ret = 1;
	}

	i2c->addr = msgs[0].addr;
	i2c->busy = true;
	i2c->state = STATE_START;
	i2c->processed = 0;
	i2c->error = 0;

	rk3x_i2c_clean_ipd(i2c);

	return ret;
}