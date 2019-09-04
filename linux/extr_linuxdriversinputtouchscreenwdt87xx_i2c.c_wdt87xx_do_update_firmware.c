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
struct wdt87xx_data {int /*<<< orphan*/  fw_mutex; int /*<<< orphan*/  param; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct wdt87xx_data* i2c_get_clientdata (struct i2c_client*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wdt87xx_get_sysparam (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int wdt87xx_load_chunk (struct i2c_client*,struct firmware const*,unsigned int) ; 
 int wdt87xx_sw_reset (struct i2c_client*) ; 
 int wdt87xx_validate_firmware (struct wdt87xx_data*,struct firmware const*) ; 

__attribute__((used)) static int wdt87xx_do_update_firmware(struct i2c_client *client,
				      const struct firmware *fw,
				      unsigned int chunk_id)
{
	struct wdt87xx_data *wdt = i2c_get_clientdata(client);
	int error;

	error = wdt87xx_validate_firmware(wdt, fw);
	if (error)
		return error;

	error = mutex_lock_interruptible(&wdt->fw_mutex);
	if (error)
		return error;

	disable_irq(client->irq);

	error = wdt87xx_load_chunk(client, fw, chunk_id);
	if (error) {
		dev_err(&client->dev,
			"firmware load failed (type: %d): %d\n",
			chunk_id, error);
		goto out;
	}

	error = wdt87xx_sw_reset(client);
	if (error) {
		dev_err(&client->dev, "soft reset failed: %d\n", error);
		goto out;
	}

	/* Refresh the parameters */
	error = wdt87xx_get_sysparam(client, &wdt->param);
	if (error)
		dev_err(&client->dev,
			"failed to refresh system parameters: %d\n", error);
out:
	enable_irq(client->irq);
	mutex_unlock(&wdt->fw_mutex);

	return error ? error : 0;
}