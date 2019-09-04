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
struct hdmi_i2c_dev {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_HI2CHCR ; 
 int /*<<< orphan*/  HDMI_HISR ; 
 int HDMI_INTR_I2C_DONE ; 
 int HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int HI2C_ENABLE_TRANSACTION ; 
 int /*<<< orphan*/  I2C_TRANSACTION_DONE ; 

__attribute__((used)) static void hdmi_i2c_transaction_done(struct oaktrail_hdmi_dev *hdmi_dev)
{
	struct hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	u32 temp;

	/* clear transaction done intr */
	temp = HDMI_READ(HDMI_HISR);
	HDMI_WRITE(HDMI_HISR, temp | HDMI_INTR_I2C_DONE);
	HDMI_READ(HDMI_HISR);


	temp = HDMI_READ(HDMI_HI2CHCR);
	HDMI_WRITE(HDMI_HI2CHCR, temp & ~HI2C_ENABLE_TRANSACTION);
	HDMI_READ(HDMI_HI2CHCR);

	i2c_dev->status = I2C_TRANSACTION_DONE;
	return;
}