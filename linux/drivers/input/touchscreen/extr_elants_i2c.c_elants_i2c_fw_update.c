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
struct firmware {int size; } ;
struct elants_data {scalar_t__ iap_mode; int /*<<< orphan*/  state; int /*<<< orphan*/  hw_version; struct i2c_client* client; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELAN_FW_PAGESIZE ; 
 scalar_t__ ELAN_IAP_OPERATIONAL ; 
 scalar_t__ ELAN_IAP_RECOVERY ; 
 int /*<<< orphan*/  ELAN_STATE_NORMAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elants_i2c_calibrate (struct elants_data*) ; 
 int elants_i2c_do_update_firmware (struct i2c_client*,struct firmware const*,int) ; 
 int elants_i2c_initialize (struct elants_data*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elants_i2c_fw_update(struct elants_data *ts)
{
	struct i2c_client *client = ts->client;
	const struct firmware *fw;
	char *fw_name;
	int error;

	fw_name = kasprintf(GFP_KERNEL, "elants_i2c_%04x.bin", ts->hw_version);
	if (!fw_name)
		return -ENOMEM;

	dev_info(&client->dev, "requesting fw name = %s\n", fw_name);
	error = request_firmware(&fw, fw_name, &client->dev);
	kfree(fw_name);
	if (error) {
		dev_err(&client->dev, "failed to request firmware: %d\n",
			error);
		return error;
	}

	if (fw->size % ELAN_FW_PAGESIZE) {
		dev_err(&client->dev, "invalid firmware length: %zu\n",
			fw->size);
		error = -EINVAL;
		goto out;
	}

	disable_irq(client->irq);

	error = elants_i2c_do_update_firmware(client, fw,
					ts->iap_mode == ELAN_IAP_RECOVERY);
	if (error) {
		dev_err(&client->dev, "firmware update failed: %d\n", error);
		ts->iap_mode = ELAN_IAP_RECOVERY;
		goto out_enable_irq;
	}

	error = elants_i2c_initialize(ts);
	if (error) {
		dev_err(&client->dev,
			"failed to initialize device after firmware update: %d\n",
			error);
		ts->iap_mode = ELAN_IAP_RECOVERY;
		goto out_enable_irq;
	}

	ts->iap_mode = ELAN_IAP_OPERATIONAL;

out_enable_irq:
	ts->state = ELAN_STATE_NORMAL;
	enable_irq(client->irq);
	msleep(100);

	if (!error)
		elants_i2c_calibrate(ts);
out:
	release_firmware(fw);
	return error;
}