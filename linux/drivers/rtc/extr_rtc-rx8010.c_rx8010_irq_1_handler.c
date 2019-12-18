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
struct rx8010_data {TYPE_1__* rtc; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ops_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int RTC_PF ; 
 int RTC_UF ; 
 int /*<<< orphan*/  RX8010_FLAG ; 
 int RX8010_FLAG_AF ; 
 int RX8010_FLAG_TF ; 
 int RX8010_FLAG_UF ; 
 int RX8010_FLAG_VLF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct rx8010_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_1__*,int,int) ; 

__attribute__((used)) static irqreturn_t rx8010_irq_1_handler(int irq, void *dev_id)
{
	struct i2c_client *client = dev_id;
	struct rx8010_data *rx8010 = i2c_get_clientdata(client);
	int flagreg;

	mutex_lock(&rx8010->rtc->ops_lock);

	flagreg = i2c_smbus_read_byte_data(client, RX8010_FLAG);

	if (flagreg <= 0) {
		mutex_unlock(&rx8010->rtc->ops_lock);
		return IRQ_NONE;
	}

	if (flagreg & RX8010_FLAG_VLF)
		dev_warn(&client->dev, "Frequency stop detected\n");

	if (flagreg & RX8010_FLAG_TF) {
		flagreg &= ~RX8010_FLAG_TF;
		rtc_update_irq(rx8010->rtc, 1, RTC_PF | RTC_IRQF);
	}

	if (flagreg & RX8010_FLAG_AF) {
		flagreg &= ~RX8010_FLAG_AF;
		rtc_update_irq(rx8010->rtc, 1, RTC_AF | RTC_IRQF);
	}

	if (flagreg & RX8010_FLAG_UF) {
		flagreg &= ~RX8010_FLAG_UF;
		rtc_update_irq(rx8010->rtc, 1, RTC_UF | RTC_IRQF);
	}

	i2c_smbus_write_byte_data(client, RX8010_FLAG, flagreg);

	mutex_unlock(&rx8010->rtc->ops_lock);
	return IRQ_HANDLED;
}