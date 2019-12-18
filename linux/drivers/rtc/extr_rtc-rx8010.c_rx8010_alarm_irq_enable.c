#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rx8010_data {int ctrlreg; int /*<<< orphan*/  client; TYPE_3__* rtc; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {scalar_t__ enabled; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_6__ {TYPE_2__ aie_timer; TYPE_1__ uie_rtctimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX8010_CTRL ; 
 int RX8010_CTRL_AIE ; 
 int RX8010_CTRL_UIE ; 
 int /*<<< orphan*/  RX8010_FLAG ; 
 int RX8010_FLAG_AF ; 
 struct rx8010_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int rx8010_alarm_irq_enable(struct device *dev,
				   unsigned int enabled)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rx8010_data *rx8010 = dev_get_drvdata(dev);
	int flagreg;
	u8 ctrl;
	int err;

	ctrl = rx8010->ctrlreg;

	if (enabled) {
		if (rx8010->rtc->uie_rtctimer.enabled)
			ctrl |= RX8010_CTRL_UIE;
		if (rx8010->rtc->aie_timer.enabled)
			ctrl |= (RX8010_CTRL_AIE | RX8010_CTRL_UIE);
	} else {
		if (!rx8010->rtc->uie_rtctimer.enabled)
			ctrl &= ~RX8010_CTRL_UIE;
		if (!rx8010->rtc->aie_timer.enabled)
			ctrl &= ~RX8010_CTRL_AIE;
	}

	flagreg = i2c_smbus_read_byte_data(client, RX8010_FLAG);
	if (flagreg < 0)
		return flagreg;

	flagreg &= ~RX8010_FLAG_AF;
	err = i2c_smbus_write_byte_data(rx8010->client, RX8010_FLAG, flagreg);
	if (err < 0)
		return err;

	if (ctrl != rx8010->ctrlreg) {
		rx8010->ctrlreg = ctrl;
		err = i2c_smbus_write_byte_data(rx8010->client, RX8010_CTRL,
						rx8010->ctrlreg);
		if (err < 0)
			return err;
	}

	return 0;
}