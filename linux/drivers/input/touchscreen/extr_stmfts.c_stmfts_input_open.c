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
 int /*<<< orphan*/  STMFTS_MS_KEY_SENSE_ON ; 
 int /*<<< orphan*/  STMFTS_MS_MT_SENSE_ON ; 
 int /*<<< orphan*/  STMFTS_SS_HOVER_SENSE_ON ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct stmfts_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stmfts_input_open(struct input_dev *dev)
{
	struct stmfts_data *sdata = input_get_drvdata(dev);
	int err;

	err = pm_runtime_get_sync(&sdata->client->dev);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte(sdata->client, STMFTS_MS_MT_SENSE_ON);
	if (err)
		return err;

	mutex_lock(&sdata->mutex);
	sdata->running = true;

	if (sdata->hover_enabled) {
		err = i2c_smbus_write_byte(sdata->client,
					   STMFTS_SS_HOVER_SENSE_ON);
		if (err)
			dev_warn(&sdata->client->dev,
				 "failed to enable hover\n");
	}
	mutex_unlock(&sdata->mutex);

	if (sdata->use_key) {
		err = i2c_smbus_write_byte(sdata->client,
					   STMFTS_MS_KEY_SENSE_ON);
		if (err)
			/* I can still use only the touch screen */
			dev_warn(&sdata->client->dev,
				 "failed to enable touchkey\n");
	}

	return 0;
}