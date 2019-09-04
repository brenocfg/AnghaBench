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
struct zforce_ts {scalar_t__ suspended; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t zforce_irq(int irq, void *dev_id)
{
	struct zforce_ts *ts = dev_id;
	struct i2c_client *client = ts->client;

	if (ts->suspended && device_may_wakeup(&client->dev))
		pm_wakeup_event(&client->dev, 500);

	return IRQ_WAKE_THREAD;
}