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
struct TYPE_2__ {int /*<<< orphan*/  hw_ver; } ;
struct raydium_data {void* boot_mode; TYPE_1__ info; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* RAYDIUM_TS_BLDR ; 
 void* RAYDIUM_TS_MAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int raydium_i2c_do_update_firmware (struct raydium_data*,struct firmware const*) ; 
 int raydium_i2c_initialize (struct raydium_data*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raydium_i2c_fw_update(struct raydium_data *ts)
{
	struct i2c_client *client = ts->client;
	const struct firmware *fw = NULL;
	char *fw_file;
	int error;

	fw_file = kasprintf(GFP_KERNEL, "raydium_%#04x.fw",
			    le32_to_cpu(ts->info.hw_ver));
	if (!fw_file)
		return -ENOMEM;

	dev_dbg(&client->dev, "firmware name: %s\n", fw_file);

	error = request_firmware(&fw, fw_file, &client->dev);
	if (error) {
		dev_err(&client->dev, "Unable to open firmware %s\n", fw_file);
		goto out_free_fw_file;
	}

	disable_irq(client->irq);

	error = raydium_i2c_do_update_firmware(ts, fw);
	if (error) {
		dev_err(&client->dev, "firmware update failed: %d\n", error);
		ts->boot_mode = RAYDIUM_TS_BLDR;
		goto out_enable_irq;
	}

	error = raydium_i2c_initialize(ts);
	if (error) {
		dev_err(&client->dev,
			"failed to initialize device after firmware update: %d\n",
			error);
		ts->boot_mode = RAYDIUM_TS_BLDR;
		goto out_enable_irq;
	}

	ts->boot_mode = RAYDIUM_TS_MAIN;

out_enable_irq:
	enable_irq(client->irq);
	msleep(100);

	release_firmware(fw);

out_free_fw_file:
	kfree(fw_file);

	return error;
}