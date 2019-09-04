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
struct oaktrail_hdmi_dev {struct hdmi_i2c_dev* i2c_dev; } ;
struct hdmi_i2c_dev {int /*<<< orphan*/  complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_HISR ; 
 int HDMI_INTR_HPD ; 
 int HDMI_INTR_I2C_DONE ; 
 int HDMI_INTR_I2C_FULL ; 
 int HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_i2c_read (struct oaktrail_hdmi_dev*) ; 
 int /*<<< orphan*/  hdmi_i2c_transaction_done (struct oaktrail_hdmi_dev*) ; 

__attribute__((used)) static irqreturn_t oaktrail_hdmi_i2c_handler(int this_irq, void *dev)
{
	struct oaktrail_hdmi_dev *hdmi_dev = dev;
	struct hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	u32 stat;

	stat = HDMI_READ(HDMI_HISR);

	if (stat & HDMI_INTR_HPD) {
		HDMI_WRITE(HDMI_HISR, stat | HDMI_INTR_HPD);
		HDMI_READ(HDMI_HISR);
	}

	if (stat & HDMI_INTR_I2C_FULL)
		hdmi_i2c_read(hdmi_dev);

	if (stat & HDMI_INTR_I2C_DONE)
		hdmi_i2c_transaction_done(hdmi_dev);

	complete(&i2c_dev->complete);

	return IRQ_HANDLED;
}