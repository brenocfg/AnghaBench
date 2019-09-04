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
struct i2c_msg {int len; } ;
struct i2c_adapter {int dummy; } ;
struct hdmi_i2c_dev {scalar_t__ status; int /*<<< orphan*/  complete; scalar_t__ buf_offset; struct i2c_msg* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_HI2CHCR ; 
 int /*<<< orphan*/  HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int HI2C_EDID_READ ; 
 int HI2C_ENABLE_TRANSACTION ; 
 int HZ ; 
 scalar_t__ I2C_STAT_INIT ; 
 scalar_t__ I2C_TRANSACTION_DONE ; 
 struct oaktrail_hdmi_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int xfer_read(struct i2c_adapter *adap, struct i2c_msg *pmsg)
{
	struct oaktrail_hdmi_dev *hdmi_dev = i2c_get_adapdata(adap);
	struct hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	u32 temp;

	i2c_dev->status = I2C_STAT_INIT;
	i2c_dev->msg = pmsg;
	i2c_dev->buf_offset = 0;
	reinit_completion(&i2c_dev->complete);

	/* Enable I2C transaction */
	temp = ((pmsg->len) << 20) | HI2C_EDID_READ | HI2C_ENABLE_TRANSACTION;
	HDMI_WRITE(HDMI_HI2CHCR, temp);
	HDMI_READ(HDMI_HI2CHCR);

	while (i2c_dev->status != I2C_TRANSACTION_DONE)
		wait_for_completion_interruptible_timeout(&i2c_dev->complete,
								10 * HZ);

	return 0;
}