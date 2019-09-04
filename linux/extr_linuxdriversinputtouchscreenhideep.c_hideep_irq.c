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
struct hideep_ts {TYPE_1__* client; int /*<<< orphan*/  xfer_buf; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  HIDEEP_EVENT_ADDR ; 
 int HIDEEP_MAX_EVENT ; 
 int HIDEEP_XFER_BUF_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hideep_parse_and_report (struct hideep_ts*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t hideep_irq(int irq, void *handle)
{
	struct hideep_ts *ts = handle;
	int error;

	BUILD_BUG_ON(HIDEEP_MAX_EVENT > HIDEEP_XFER_BUF_SIZE);

	error = regmap_bulk_read(ts->reg, HIDEEP_EVENT_ADDR,
				 ts->xfer_buf, HIDEEP_MAX_EVENT / 2);
	if (error) {
		dev_err(&ts->client->dev, "failed to read events: %d\n", error);
		goto out;
	}

	hideep_parse_and_report(ts);

out:
	return IRQ_HANDLED;
}