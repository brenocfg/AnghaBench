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
typedef  int u16 ;
struct i2c_msg {int addr; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; } ;
struct hdmi {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int msm_hdmi_ddc_read(struct hdmi *hdmi, u16 addr, u8 offset,
	u8 *data, u16 data_len)
{
	int rc;
	int retry = 5;
	struct i2c_msg msgs[] = {
		{
			.addr	= addr >> 1,
			.flags	= 0,
			.len	= 1,
			.buf	= &offset,
		}, {
			.addr	= addr >> 1,
			.flags	= I2C_M_RD,
			.len	= data_len,
			.buf	= data,
		}
	};

	DBG("Start DDC read");
retry:
	rc = i2c_transfer(hdmi->i2c, msgs, 2);

	retry--;
	if (rc == 2)
		rc = 0;
	else if (retry > 0)
		goto retry;
	else
		rc = -EIO;

	DBG("End DDC read %d", rc);

	return rc;
}