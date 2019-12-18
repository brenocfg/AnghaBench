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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct axxia_i2c_dev {scalar_t__ base; int /*<<< orphan*/  slave; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_SLAVE_READ_PROCESSED ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_REQUESTED ; 
 int /*<<< orphan*/  I2C_SLAVE_STOP ; 
 scalar_t__ INTERRUPT_STATUS ; 
 int /*<<< orphan*/  INT_SLV ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SLV_DATA ; 
 scalar_t__ SLV_INT_STATUS ; 
 int SLV_STATUS_RFH ; 
 int SLV_STATUS_SRC1 ; 
 int SLV_STATUS_SRND1 ; 
 int SLV_STATUS_SRS1 ; 
 int /*<<< orphan*/  axxia_i2c_slv_fifo_event (struct axxia_i2c_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  i2c_slave_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t axxia_i2c_slv_isr(struct axxia_i2c_dev *idev)
{
	u32 status = readl(idev->base + SLV_INT_STATUS);
	u8 val;

	dev_dbg(idev->dev, "slave irq status=0x%x\n", status);

	if (status & SLV_STATUS_RFH)
		axxia_i2c_slv_fifo_event(idev);
	if (status & SLV_STATUS_SRS1) {
		i2c_slave_event(idev->slave, I2C_SLAVE_READ_REQUESTED, &val);
		writel(val, idev->base + SLV_DATA);
	}
	if (status & SLV_STATUS_SRND1) {
		i2c_slave_event(idev->slave, I2C_SLAVE_READ_PROCESSED, &val);
		writel(val, idev->base + SLV_DATA);
	}
	if (status & SLV_STATUS_SRC1)
		i2c_slave_event(idev->slave, I2C_SLAVE_STOP, &val);

	writel(INT_SLV, idev->base + INTERRUPT_STATUS);
	return IRQ_HANDLED;
}