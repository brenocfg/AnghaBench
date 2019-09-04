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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cyapa {int /*<<< orphan*/  state_sync_lock; int /*<<< orphan*/ * input; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int NAME_MAX ; 
 int cyapa_firmware (struct cyapa*,char*) ; 
 int cyapa_reinitialize (struct cyapa*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct cyapa* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t cyapa_update_fw_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cyapa *cyapa = dev_get_drvdata(dev);
	char fw_name[NAME_MAX];
	int ret, error;

	if (count >= NAME_MAX) {
		dev_err(dev, "File name too long\n");
		return -EINVAL;
	}

	memcpy(fw_name, buf, count);
	if (fw_name[count - 1] == '\n')
		fw_name[count - 1] = '\0';
	else
		fw_name[count] = '\0';

	if (cyapa->input) {
		/*
		 * Force the input device to be registered after the firmware
		 * image is updated, so if the corresponding parameters updated
		 * in the new firmware image can taken effect immediately.
		 */
		input_unregister_device(cyapa->input);
		cyapa->input = NULL;
	}

	error = mutex_lock_interruptible(&cyapa->state_sync_lock);
	if (error) {
		/*
		 * Whatever, do reinitialize to try to recover TP state to
		 * previous state just as it entered fw update entrance.
		 */
		cyapa_reinitialize(cyapa);
		return error;
	}

	error = cyapa_firmware(cyapa, fw_name);
	if (error)
		dev_err(dev, "firmware update failed: %d\n", error);
	else
		dev_dbg(dev, "firmware update successfully done.\n");

	/*
	 * Re-detect trackpad device states because firmware update process
	 * will reset trackpad device into bootloader mode.
	 */
	ret = cyapa_reinitialize(cyapa);
	if (ret) {
		dev_err(dev, "failed to re-detect after updated: %d\n", ret);
		error = error ? error : ret;
	}

	mutex_unlock(&cyapa->state_sync_lock);

	return error ? error : count;
}