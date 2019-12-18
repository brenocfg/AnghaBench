#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  alarm ;

/* Variables and functions */
 int ABX8XX_IRQ_AIE ; 
 int ABX8XX_IRQ_IM_1_4 ; 
 int /*<<< orphan*/  ABX8XX_REG_AHTH ; 
 int /*<<< orphan*/  ABX8XX_REG_IRQ ; 
 int EINVAL ; 
 int EIO ; 
 int bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int abx80x_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 alarm[6];
	int err;

	if (client->irq <= 0)
		return -EINVAL;

	alarm[0] = 0x0;
	alarm[1] = bin2bcd(t->time.tm_sec);
	alarm[2] = bin2bcd(t->time.tm_min);
	alarm[3] = bin2bcd(t->time.tm_hour);
	alarm[4] = bin2bcd(t->time.tm_mday);
	alarm[5] = bin2bcd(t->time.tm_mon + 1);

	err = i2c_smbus_write_i2c_block_data(client, ABX8XX_REG_AHTH,
					     sizeof(alarm), alarm);
	if (err < 0) {
		dev_err(&client->dev, "Unable to write alarm registers\n");
		return -EIO;
	}

	if (t->enabled) {
		err = i2c_smbus_write_byte_data(client, ABX8XX_REG_IRQ,
						(ABX8XX_IRQ_IM_1_4 |
						 ABX8XX_IRQ_AIE));
		if (err)
			return err;
	}

	return 0;
}