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
struct dw_i2c_dev {int /*<<< orphan*/  slave; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_CLR_RD_REQ ; 
 int /*<<< orphan*/  DW_IC_CLR_RX_DONE ; 
 int /*<<< orphan*/  DW_IC_CLR_RX_UNDER ; 
 int /*<<< orphan*/  DW_IC_DATA_CMD ; 
 int /*<<< orphan*/  DW_IC_ENABLE ; 
 int DW_IC_INTR_ACTIVITY ; 
 int DW_IC_INTR_RD_REQ ; 
 int DW_IC_INTR_RX_DONE ; 
 int DW_IC_INTR_RX_FULL ; 
 int /*<<< orphan*/  DW_IC_INTR_STAT ; 
 int DW_IC_INTR_STOP_DET ; 
 int /*<<< orphan*/  DW_IC_RAW_INTR_STAT ; 
 int /*<<< orphan*/  DW_IC_STATUS ; 
 int DW_IC_STATUS_SLAVE_ACTIVITY ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_PROCESSED ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_REQUESTED ; 
 int /*<<< orphan*/  I2C_SLAVE_STOP ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_RECEIVED ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_REQUESTED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_writel (struct dw_i2c_dev*,int,int /*<<< orphan*/ ) ; 
 int i2c_dw_read_clear_intrbits_slave (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_slave_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int i2c_dw_irq_handler_slave(struct dw_i2c_dev *dev)
{
	u32 raw_stat, stat, enabled;
	u8 val, slave_activity;

	stat = dw_readl(dev, DW_IC_INTR_STAT);
	enabled = dw_readl(dev, DW_IC_ENABLE);
	raw_stat = dw_readl(dev, DW_IC_RAW_INTR_STAT);
	slave_activity = ((dw_readl(dev, DW_IC_STATUS) &
		DW_IC_STATUS_SLAVE_ACTIVITY) >> 6);

	if (!enabled || !(raw_stat & ~DW_IC_INTR_ACTIVITY) || !dev->slave)
		return 0;

	dev_dbg(dev->dev,
		"%#x STATUS SLAVE_ACTIVITY=%#x : RAW_INTR_STAT=%#x : INTR_STAT=%#x\n",
		enabled, slave_activity, raw_stat, stat);

	if ((stat & DW_IC_INTR_RX_FULL) && (stat & DW_IC_INTR_STOP_DET))
		i2c_slave_event(dev->slave, I2C_SLAVE_WRITE_REQUESTED, &val);

	if (stat & DW_IC_INTR_RD_REQ) {
		if (slave_activity) {
			if (stat & DW_IC_INTR_RX_FULL) {
				val = dw_readl(dev, DW_IC_DATA_CMD);

				if (!i2c_slave_event(dev->slave,
						     I2C_SLAVE_WRITE_RECEIVED,
						     &val)) {
					dev_vdbg(dev->dev, "Byte %X acked!",
						 val);
				}
				dw_readl(dev, DW_IC_CLR_RD_REQ);
				stat = i2c_dw_read_clear_intrbits_slave(dev);
			} else {
				dw_readl(dev, DW_IC_CLR_RD_REQ);
				dw_readl(dev, DW_IC_CLR_RX_UNDER);
				stat = i2c_dw_read_clear_intrbits_slave(dev);
			}
			if (!i2c_slave_event(dev->slave,
					     I2C_SLAVE_READ_REQUESTED,
					     &val))
				dw_writel(dev, val, DW_IC_DATA_CMD);
		}
	}

	if (stat & DW_IC_INTR_RX_DONE) {
		if (!i2c_slave_event(dev->slave, I2C_SLAVE_READ_PROCESSED,
				     &val))
			dw_readl(dev, DW_IC_CLR_RX_DONE);

		i2c_slave_event(dev->slave, I2C_SLAVE_STOP, &val);
		stat = i2c_dw_read_clear_intrbits_slave(dev);
		return 1;
	}

	if (stat & DW_IC_INTR_RX_FULL) {
		val = dw_readl(dev, DW_IC_DATA_CMD);
		if (!i2c_slave_event(dev->slave, I2C_SLAVE_WRITE_RECEIVED,
				     &val))
			dev_vdbg(dev->dev, "Byte %X acked!", val);
	} else {
		i2c_slave_event(dev->slave, I2C_SLAVE_STOP, &val);
		stat = i2c_dw_read_clear_intrbits_slave(dev);
	}

	return 1;
}