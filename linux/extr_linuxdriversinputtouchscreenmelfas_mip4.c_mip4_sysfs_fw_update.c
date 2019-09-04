#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mip4_ts {TYPE_2__* client; TYPE_1__* input; int /*<<< orphan*/  fw_name; } ;
struct i2c_client {int dummy; } ;
struct firmware {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct mip4_ts* i2c_get_clientdata (struct i2c_client*) ; 
 int mip4_execute_fw_update (struct mip4_ts*,struct firmware const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t mip4_sysfs_fw_update(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mip4_ts *ts = i2c_get_clientdata(client);
	const struct firmware *fw;
	int error;

	error = request_firmware(&fw, ts->fw_name, dev);
	if (error) {
		dev_err(&ts->client->dev,
			"Failed to retrieve firmware %s: %d\n",
			ts->fw_name, error);
		return error;
	}

	/*
	 * Take input mutex to prevent racing with itself and also with
	 * userspace opening and closing the device and also suspend/resume
	 * transitions.
	 */
	mutex_lock(&ts->input->mutex);

	error = mip4_execute_fw_update(ts, fw);

	mutex_unlock(&ts->input->mutex);

	release_firmware(fw);

	if (error) {
		dev_err(&ts->client->dev,
			"Firmware update failed: %d\n", error);
		return error;
	}

	return count;
}