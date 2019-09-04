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
struct synquacer_i2c {int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  pclkrate; } ;
struct i2c_msg {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 unsigned char SYNQUACER_I2C_BCR_BEIE ; 
 unsigned char SYNQUACER_I2C_BCR_INTE ; 
 unsigned char SYNQUACER_I2C_BCR_MSS ; 
 unsigned char SYNQUACER_I2C_BCR_SCC ; 
 unsigned char SYNQUACER_I2C_BSR_AL ; 
 unsigned char SYNQUACER_I2C_BSR_BB ; 
 scalar_t__ SYNQUACER_I2C_REG_BCR ; 
 scalar_t__ SYNQUACER_I2C_REG_BSR ; 
 scalar_t__ SYNQUACER_I2C_REG_DAR ; 
 int /*<<< orphan*/  WAIT_PCLK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int synquacer_i2c_master_start(struct synquacer_i2c *i2c,
				      struct i2c_msg *pmsg)
{
	unsigned char bsr, bcr;

	writeb(i2c_8bit_addr_from_msg(pmsg), i2c->base + SYNQUACER_I2C_REG_DAR);

	dev_dbg(i2c->dev, "slave:0x%02x\n", pmsg->addr);

	/* Generate Start Condition */
	bsr = readb(i2c->base + SYNQUACER_I2C_REG_BSR);
	bcr = readb(i2c->base + SYNQUACER_I2C_REG_BCR);
	dev_dbg(i2c->dev, "bsr:0x%02x, bcr:0x%02x\n", bsr, bcr);

	if ((bsr & SYNQUACER_I2C_BSR_BB) &&
	    !(bcr & SYNQUACER_I2C_BCR_MSS)) {
		dev_dbg(i2c->dev, "bus is busy");
		return -EBUSY;
	}

	if (bsr & SYNQUACER_I2C_BSR_BB) { /* Bus is busy */
		dev_dbg(i2c->dev, "Continuous Start");
		writeb(bcr | SYNQUACER_I2C_BCR_SCC,
		       i2c->base + SYNQUACER_I2C_REG_BCR);
	} else {
		if (bcr & SYNQUACER_I2C_BCR_MSS) {
			dev_dbg(i2c->dev, "not in master mode");
			return -EAGAIN;
		}
		dev_dbg(i2c->dev, "Start Condition");
		/* Start Condition + Enable Interrupts */
		writeb(bcr | SYNQUACER_I2C_BCR_MSS |
		       SYNQUACER_I2C_BCR_INTE | SYNQUACER_I2C_BCR_BEIE,
		       i2c->base + SYNQUACER_I2C_REG_BCR);
	}

	WAIT_PCLK(10, i2c->pclkrate);

	/* get BSR & BCR registers */
	bsr = readb(i2c->base + SYNQUACER_I2C_REG_BSR);
	bcr = readb(i2c->base + SYNQUACER_I2C_REG_BCR);
	dev_dbg(i2c->dev, "bsr:0x%02x, bcr:0x%02x\n", bsr, bcr);

	if ((bsr & SYNQUACER_I2C_BSR_AL) ||
	    !(bcr & SYNQUACER_I2C_BCR_MSS)) {
		dev_dbg(i2c->dev, "arbitration lost\n");
		return -EAGAIN;
	}

	return 0;
}