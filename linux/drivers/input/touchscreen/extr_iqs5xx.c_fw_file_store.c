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
struct iqs5xx_private {int /*<<< orphan*/  input; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int IQS5XX_FW_FILE_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct iqs5xx_private* dev_get_drvdata (struct device*) ; 
 int input_register_device (int /*<<< orphan*/ ) ; 
 int iqs5xx_fw_file_write (struct i2c_client*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static ssize_t fw_file_store(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct iqs5xx_private *iqs5xx = dev_get_drvdata(dev);
	struct i2c_client *client = iqs5xx->client;
	size_t len = count;
	bool input_reg = !iqs5xx->input;
	char fw_file[IQS5XX_FW_FILE_LEN + 1];
	int error;

	if (!len)
		return -EINVAL;

	if (buf[len - 1] == '\n')
		len--;

	if (len > IQS5XX_FW_FILE_LEN)
		return -ENAMETOOLONG;

	memcpy(fw_file, buf, len);
	fw_file[len] = '\0';

	error = iqs5xx_fw_file_write(client, fw_file);
	if (error)
		return error;

	/*
	 * If the input device was not allocated already, it is guaranteed to
	 * be allocated by this point and can finally be registered.
	 */
	if (input_reg) {
		error = input_register_device(iqs5xx->input);
		if (error) {
			dev_err(&client->dev,
				"Failed to register device: %d\n",
				error);
			return error;
		}
	}

	return count;
}