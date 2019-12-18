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
struct rtc_device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct abx80x_priv {struct rtc_device* rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABX8XX_REG_STATUS ; 
 int ABX8XX_STATUS_AF ; 
 int ABX8XX_STATUS_WDT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*) ; 
 struct abx80x_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int) ; 

__attribute__((used)) static irqreturn_t abx80x_handle_irq(int irq, void *dev_id)
{
	struct i2c_client *client = dev_id;
	struct abx80x_priv *priv = i2c_get_clientdata(client);
	struct rtc_device *rtc = priv->rtc;
	int status;

	status = i2c_smbus_read_byte_data(client, ABX8XX_REG_STATUS);
	if (status < 0)
		return IRQ_NONE;

	if (status & ABX8XX_STATUS_AF)
		rtc_update_irq(rtc, 1, RTC_AF | RTC_IRQF);

	/*
	 * It is unclear if we'll get an interrupt before the external
	 * reset kicks in.
	 */
	if (status & ABX8XX_STATUS_WDT)
		dev_alert(&client->dev, "watchdog timeout interrupt.\n");

	i2c_smbus_write_byte_data(client, ABX8XX_REG_STATUS, 0);

	return IRQ_HANDLED;
}