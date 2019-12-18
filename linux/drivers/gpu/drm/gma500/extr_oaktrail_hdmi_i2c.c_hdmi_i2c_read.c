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
struct oaktrail_hdmi_dev {struct hdmi_i2c_dev* i2c_dev; } ;
struct i2c_msg {int /*<<< orphan*/ * buf; } ;
struct hdmi_i2c_dev {int buf_offset; int /*<<< orphan*/  status; struct i2c_msg* msg; } ;

/* Variables and functions */
 scalar_t__ HDMI_HI2CHCR ; 
 scalar_t__ HDMI_HI2CRDB0 ; 
 scalar_t__ HDMI_HISR ; 
 int HDMI_INTR_I2C_FULL ; 
 int HDMI_READ (scalar_t__) ; 
 int /*<<< orphan*/  HDMI_WRITE (scalar_t__,int) ; 
 int HI2C_READ_CONTINUE ; 
 int /*<<< orphan*/  I2C_READ_DONE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void hdmi_i2c_read(struct oaktrail_hdmi_dev *hdmi_dev)
{
	struct hdmi_i2c_dev *i2c_dev = hdmi_dev->i2c_dev;
	struct i2c_msg *msg = i2c_dev->msg;
	u8 *buf = msg->buf;
	u32 temp;
	int i, offset;

	offset = i2c_dev->buf_offset;
	for (i = 0; i < 0x10; i++) {
		temp = HDMI_READ(HDMI_HI2CRDB0 + (i * 4));
		memcpy(buf + (offset + i * 4), &temp, 4);
	}
	i2c_dev->buf_offset += (0x10 * 4);

	/* clearing read buffer full intr */
	temp = HDMI_READ(HDMI_HISR);
	HDMI_WRITE(HDMI_HISR, temp | HDMI_INTR_I2C_FULL);
	HDMI_READ(HDMI_HISR);

	/* continue read transaction */
	temp = HDMI_READ(HDMI_HI2CHCR);
	HDMI_WRITE(HDMI_HI2CHCR, temp | HI2C_READ_CONTINUE);
	HDMI_READ(HDMI_HI2CHCR);

	i2c_dev->status = I2C_READ_DONE;
	return;
}