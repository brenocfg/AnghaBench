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
struct eeti_ts {TYPE_1__* client; scalar_t__ attn_gpio; scalar_t__ running; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  eeti_ts_report_event (struct eeti_ts*,char*) ; 
 scalar_t__ gpiod_get_value_cansleep (scalar_t__) ; 
 int i2c_master_recv (TYPE_1__*,char*,int) ; 

__attribute__((used)) static irqreturn_t eeti_ts_isr(int irq, void *dev_id)
{
	struct eeti_ts *eeti = dev_id;
	int len;
	int error;
	char buf[6];

	do {
		len = i2c_master_recv(eeti->client, buf, sizeof(buf));
		if (len != sizeof(buf)) {
			error = len < 0 ? len : -EIO;
			dev_err(&eeti->client->dev,
				"failed to read touchscreen data: %d\n",
				error);
			break;
		}

		if (buf[0] & 0x80) {
			/* Motion packet */
			eeti_ts_report_event(eeti, buf);
		}
	} while (eeti->running &&
		 eeti->attn_gpio && gpiod_get_value_cansleep(eeti->attn_gpio));

	return IRQ_HANDLED;
}