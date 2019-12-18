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
typedef  void* u8 ;
typedef  int u32 ;
struct axxia_i2c_dev {scalar_t__ base; int /*<<< orphan*/  slave; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SLAVE_STOP ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_RECEIVED ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_REQUESTED ; 
 scalar_t__ SLV_DATA ; 
 int SLV_FIFO_DV1 ; 
 int SLV_FIFO_RSC ; 
 int SLV_FIFO_STPC ; 
 int SLV_FIFO_STRC ; 
 scalar_t__ SLV_RX_FIFO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  i2c_slave_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static void axxia_i2c_slv_fifo_event(struct axxia_i2c_dev *idev)
{
	u32 fifo_status = readl(idev->base + SLV_RX_FIFO);
	u8 val;

	dev_dbg(idev->dev, "slave irq fifo_status=0x%x\n", fifo_status);

	if (fifo_status & SLV_FIFO_DV1) {
		if (fifo_status & SLV_FIFO_STRC)
			i2c_slave_event(idev->slave,
					I2C_SLAVE_WRITE_REQUESTED, &val);

		val = readl(idev->base + SLV_DATA);
		i2c_slave_event(idev->slave, I2C_SLAVE_WRITE_RECEIVED, &val);
	}
	if (fifo_status & SLV_FIFO_STPC) {
		readl(idev->base + SLV_DATA); /* dummy read */
		i2c_slave_event(idev->slave, I2C_SLAVE_STOP, &val);
	}
	if (fifo_status & SLV_FIFO_RSC)
		readl(idev->base + SLV_DATA); /* dummy read */
}