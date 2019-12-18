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
struct s6sy761_data {int* data; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int S6SY761_EVENT_COUNT ; 
 int /*<<< orphan*/  S6SY761_EVENT_SIZE ; 
 int S6SY761_MASK_LEFT_EVENTS ; 
 int /*<<< orphan*/  S6SY761_READ_ONE_EVENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_i2c_block_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  s6sy761_handle_events (struct s6sy761_data*,int) ; 
 int s6sy761_read_events (struct s6sy761_data*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t s6sy761_irq_handler(int irq, void *dev)
{
	struct s6sy761_data *sdata = dev;
	int ret;
	u8 n_events;

	ret = i2c_smbus_read_i2c_block_data(sdata->client,
					    S6SY761_READ_ONE_EVENT,
					    S6SY761_EVENT_SIZE,
					    sdata->data);
	if (ret < 0) {
		dev_err(&sdata->client->dev, "failed to read events\n");
		return IRQ_HANDLED;
	}

	if (!sdata->data[0])
		return IRQ_HANDLED;

	n_events = sdata->data[7] & S6SY761_MASK_LEFT_EVENTS;
	if (unlikely(n_events > S6SY761_EVENT_COUNT - 1))
		return IRQ_HANDLED;

	if (n_events) {
		ret = s6sy761_read_events(sdata, n_events);
		if (ret < 0) {
			dev_err(&sdata->client->dev, "failed to read events\n");
			return IRQ_HANDLED;
		}
	}

	s6sy761_handle_events(sdata, n_events +  1);

	return IRQ_HANDLED;
}