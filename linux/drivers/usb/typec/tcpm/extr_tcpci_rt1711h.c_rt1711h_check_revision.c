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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int RT1711H_PID ; 
 int RT1711H_VID ; 
 int /*<<< orphan*/  TCPC_PRODUCT_ID ; 
 int /*<<< orphan*/  TCPC_VENDOR_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt1711h_check_revision(struct i2c_client *i2c)
{
	int ret;

	ret = i2c_smbus_read_word_data(i2c, TCPC_VENDOR_ID);
	if (ret < 0)
		return ret;
	if (ret != RT1711H_VID) {
		dev_err(&i2c->dev, "vid is not correct, 0x%04x\n", ret);
		return -ENODEV;
	}
	ret = i2c_smbus_read_word_data(i2c, TCPC_PRODUCT_ID);
	if (ret < 0)
		return ret;
	if (ret != RT1711H_PID) {
		dev_err(&i2c->dev, "pid is not correct, 0x%04x\n", ret);
		return -ENODEV;
	}
	return 0;
}