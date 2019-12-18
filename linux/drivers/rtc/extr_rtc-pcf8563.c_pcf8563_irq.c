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
struct pcf8563 {int /*<<< orphan*/  client; int /*<<< orphan*/  rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 struct pcf8563* i2c_get_clientdata (void*) ; 
 int pcf8563_get_alarm_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pcf8563_set_alarm_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t pcf8563_irq(int irq, void *dev_id)
{
	struct pcf8563 *pcf8563 = i2c_get_clientdata(dev_id);
	int err;
	char pending;

	err = pcf8563_get_alarm_mode(pcf8563->client, NULL, &pending);
	if (err)
		return IRQ_NONE;

	if (pending) {
		rtc_update_irq(pcf8563->rtc, 1, RTC_IRQF | RTC_AF);
		pcf8563_set_alarm_mode(pcf8563->client, 1);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}