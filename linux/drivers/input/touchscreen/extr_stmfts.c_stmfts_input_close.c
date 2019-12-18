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
struct stmfts_data {int running; TYPE_1__* client; scalar_t__ use_key; int /*<<< orphan*/  mutex; scalar_t__ hover_enabled; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMFTS_MS_KEY_SENSE_OFF ; 
 int /*<<< orphan*/  STMFTS_MS_MT_SENSE_OFF ; 
 int /*<<< orphan*/  STMFTS_SS_HOVER_SENSE_OFF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct stmfts_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stmfts_input_close(struct input_dev *dev)
{
	struct stmfts_data *sdata = input_get_drvdata(dev);
	int err;

	err = i2c_smbus_write_byte(sdata->client, STMFTS_MS_MT_SENSE_OFF);
	if (err)
		dev_warn(&sdata->client->dev,
			 "failed to disable touchscreen: %d\n", err);

	mutex_lock(&sdata->mutex);

	sdata->running = false;

	if (sdata->hover_enabled) {
		err = i2c_smbus_write_byte(sdata->client,
					   STMFTS_SS_HOVER_SENSE_OFF);
		if (err)
			dev_warn(&sdata->client->dev,
				 "failed to disable hover: %d\n", err);
	}
	mutex_unlock(&sdata->mutex);

	if (sdata->use_key) {
		err = i2c_smbus_write_byte(sdata->client,
					   STMFTS_MS_KEY_SENSE_OFF);
		if (err)
			dev_warn(&sdata->client->dev,
				 "failed to disable touchkey: %d\n", err);
	}

	pm_runtime_put_sync(&sdata->client->dev);
}