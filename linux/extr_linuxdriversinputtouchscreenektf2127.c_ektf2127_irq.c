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
struct ektf2127_ts {TYPE_1__* client; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
#define  EKTF2127_CALIB_DONE 131 
 char EKTF2127_ENV_NOISY ; 
#define  EKTF2127_HELLO 130 
#define  EKTF2127_NOISE 129 
#define  EKTF2127_REPORT 128 
 int EKTF2127_TOUCH_REPORT_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char) ; 
 int /*<<< orphan*/  ektf2127_report_event (struct ektf2127_ts*,char*) ; 
 int i2c_master_recv (TYPE_1__*,char*,int) ; 

__attribute__((used)) static irqreturn_t ektf2127_irq(int irq, void *dev_id)
{
	struct ektf2127_ts *ts = dev_id;
	struct device *dev = &ts->client->dev;
	char buf[EKTF2127_TOUCH_REPORT_SIZE];
	int ret;

	ret = i2c_master_recv(ts->client, buf, EKTF2127_TOUCH_REPORT_SIZE);
	if (ret != EKTF2127_TOUCH_REPORT_SIZE) {
		dev_err(dev, "Error reading touch data: %d\n", ret);
		goto out;
	}

	switch (buf[0]) {
	case EKTF2127_REPORT:
		ektf2127_report_event(ts, buf);
		break;

	case EKTF2127_NOISE:
		if (buf[1] == EKTF2127_ENV_NOISY)
			dev_dbg(dev, "Environment is electrically noisy\n");
		break;

	case EKTF2127_HELLO:
	case EKTF2127_CALIB_DONE:
		break;

	default:
		dev_err(dev, "Unexpected packet header byte %#02x\n", buf[0]);
		break;
	}

out:
	return IRQ_HANDLED;
}