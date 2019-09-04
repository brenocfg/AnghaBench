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
typedef  int u8 ;
struct firmware {int* data; } ;
struct elan_tp_data {scalar_t__ fw_validpage_count; size_t fw_signature_address; int /*<<< orphan*/  sysfs_mutex; int /*<<< orphan*/  product_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  signature ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETP_FW_NAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct elan_tp_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int elan_update_firmware (struct elan_tp_data*,struct firmware const*) ; 
 char* kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ memcmp (int const*,int const*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,struct device*) ; 

__attribute__((used)) static ssize_t elan_sysfs_update_fw(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct elan_tp_data *data = dev_get_drvdata(dev);
	const struct firmware *fw;
	char *fw_name;
	int error;
	const u8 *fw_signature;
	static const u8 signature[] = {0xAA, 0x55, 0xCC, 0x33, 0xFF, 0xFF};

	if (data->fw_validpage_count == 0)
		return -EINVAL;

	/* Look for a firmware with the product id appended. */
	fw_name = kasprintf(GFP_KERNEL, ETP_FW_NAME, data->product_id);
	if (!fw_name) {
		dev_err(dev, "failed to allocate memory for firmware name\n");
		return -ENOMEM;
	}

	dev_info(dev, "requesting fw '%s'\n", fw_name);
	error = request_firmware(&fw, fw_name, dev);
	kfree(fw_name);
	if (error) {
		dev_err(dev, "failed to request firmware: %d\n", error);
		return error;
	}

	/* Firmware file must match signature data */
	fw_signature = &fw->data[data->fw_signature_address];
	if (memcmp(fw_signature, signature, sizeof(signature)) != 0) {
		dev_err(dev, "signature mismatch (expected %*ph, got %*ph)\n",
			(int)sizeof(signature), signature,
			(int)sizeof(signature), fw_signature);
		error = -EBADF;
		goto out_release_fw;
	}

	error = mutex_lock_interruptible(&data->sysfs_mutex);
	if (error)
		goto out_release_fw;

	error = elan_update_firmware(data, fw);

	mutex_unlock(&data->sysfs_mutex);

out_release_fw:
	release_firmware(fw);
	return error ?: count;
}