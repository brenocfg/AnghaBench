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
struct stmfts_data {int /*<<< orphan*/  mutex; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmfts_parse_events (struct stmfts_data*) ; 
 int stmfts_read_events (struct stmfts_data*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t stmfts_irq_handler(int irq, void *dev)
{
	struct stmfts_data *sdata = dev;
	int err;

	mutex_lock(&sdata->mutex);

	err = stmfts_read_events(sdata);
	if (unlikely(err))
		dev_err(&sdata->client->dev,
			"failed to read events: %d\n", err);
	else
		stmfts_parse_events(sdata);

	mutex_unlock(&sdata->mutex);
	return IRQ_HANDLED;
}