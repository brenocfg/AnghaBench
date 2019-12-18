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
typedef  int u16 ;
struct go7007 {scalar_t__ status; scalar_t__ board_id; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ GO7007_BOARDID_ADLINK_MPG24 ; 
 int I2C_CTRL_REG_ADDR ; 
 int I2C_DATA_REG_ADDR ; 
 int I2C_DEV_UP_ADDR_REG_ADDR ; 
 int I2C_LO_ADDR_REG_ADDR ; 
 int I2C_READ_READY_MASK ; 
 int I2C_STATE_MASK ; 
 int STATUS_REG_ADDR ; 
 scalar_t__ STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  adlink_mpg24_i2c_lock ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ go7007_read_addr (struct go7007*,int,int*) ; 
 int /*<<< orphan*/  go7007_write_addr (struct go7007*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int go7007_i2c_xfer(struct go7007 *go, u16 addr, int read,
		u16 command, int flags, u8 *data)
{
	int i, ret = -EIO;
	u16 val;

	if (go->status == STATUS_SHUTDOWN)
		return -ENODEV;

#ifdef GO7007_I2C_DEBUG
	if (read)
		dev_dbg(go->dev, "go7007-i2c: reading 0x%02x on 0x%02x\n",
			command, addr);
	else
		dev_dbg(go->dev,
			"go7007-i2c: writing 0x%02x to 0x%02x on 0x%02x\n",
			*data, command, addr);
#endif

	mutex_lock(&go->hw_lock);

	if (go->board_id == GO7007_BOARDID_ADLINK_MPG24) {
		/* Bridge the I2C port on this GO7007 to the shared bus */
		mutex_lock(&adlink_mpg24_i2c_lock);
		go7007_write_addr(go, 0x3c82, 0x0020);
	}

	/* Wait for I2C adapter to be ready */
	for (i = 0; i < 10; ++i) {
		if (go7007_read_addr(go, STATUS_REG_ADDR, &val) < 0)
			goto i2c_done;
		if (!(val & I2C_STATE_MASK))
			break;
		msleep(100);
	}
	if (i == 10) {
		dev_err(go->dev, "go7007-i2c: I2C adapter is hung\n");
		goto i2c_done;
	}

	/* Set target register (command) */
	go7007_write_addr(go, I2C_CTRL_REG_ADDR, flags);
	go7007_write_addr(go, I2C_LO_ADDR_REG_ADDR, command);

	/* If we're writing, send the data and target address and we're done */
	if (!read) {
		go7007_write_addr(go, I2C_DATA_REG_ADDR, *data);
		go7007_write_addr(go, I2C_DEV_UP_ADDR_REG_ADDR,
					(addr << 9) | (command >> 8));
		ret = 0;
		goto i2c_done;
	}

	/* Otherwise, we're reading.  First clear i2c_rx_data_rdy. */
	if (go7007_read_addr(go, I2C_DATA_REG_ADDR, &val) < 0)
		goto i2c_done;

	/* Send the target address plus read flag */
	go7007_write_addr(go, I2C_DEV_UP_ADDR_REG_ADDR,
			(addr << 9) | 0x0100 | (command >> 8));

	/* Wait for i2c_rx_data_rdy */
	for (i = 0; i < 10; ++i) {
		if (go7007_read_addr(go, STATUS_REG_ADDR, &val) < 0)
			goto i2c_done;
		if (val & I2C_READ_READY_MASK)
			break;
		msleep(100);
	}
	if (i == 10) {
		dev_err(go->dev, "go7007-i2c: I2C adapter is hung\n");
		goto i2c_done;
	}

	/* Retrieve the read byte */
	if (go7007_read_addr(go, I2C_DATA_REG_ADDR, &val) < 0)
		goto i2c_done;
	*data = val;
	ret = 0;

i2c_done:
	if (go->board_id == GO7007_BOARDID_ADLINK_MPG24) {
		/* Isolate the I2C port on this GO7007 from the shared bus */
		go7007_write_addr(go, 0x3c82, 0x0000);
		mutex_unlock(&adlink_mpg24_i2c_lock);
	}
	mutex_unlock(&go->hw_lock);
	return ret;
}