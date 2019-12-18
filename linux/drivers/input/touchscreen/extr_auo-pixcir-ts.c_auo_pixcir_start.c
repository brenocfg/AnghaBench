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
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct auo_pixcir_ts {int stopped; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUO_PIXCIR_POWER_ACTIVE ; 
 int auo_pixcir_int_toggle (struct auo_pixcir_ts*,int) ; 
 int auo_pixcir_power_mode (struct auo_pixcir_ts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int auo_pixcir_start(struct auo_pixcir_ts *ts)
{
	struct i2c_client *client = ts->client;
	int ret;

	ret = auo_pixcir_power_mode(ts, AUO_PIXCIR_POWER_ACTIVE);
	if (ret < 0) {
		dev_err(&client->dev, "could not set power mode, %d\n",
			ret);
		return ret;
	}

	ts->stopped = false;
	mb();
	enable_irq(client->irq);

	ret = auo_pixcir_int_toggle(ts, 1);
	if (ret < 0) {
		dev_err(&client->dev, "could not enable interrupt, %d\n",
			ret);
		disable_irq(client->irq);
		return ret;
	}

	return 0;
}