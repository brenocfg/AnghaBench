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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,struct device*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int wdt87xx_do_update_firmware (struct i2c_client*,struct firmware const*,unsigned int) ; 

__attribute__((used)) static int wdt87xx_update_firmware(struct device *dev,
				   const char *fw_name, unsigned int chunk_id)
{
	struct i2c_client *client = to_i2c_client(dev);
	const struct firmware *fw;
	int error;

	error = request_firmware(&fw, fw_name, dev);
	if (error) {
		dev_err(&client->dev, "unable to retrieve firmware %s: %d\n",
			fw_name, error);
		return error;
	}

	error = wdt87xx_do_update_firmware(client, fw, chunk_id);

	release_firmware(fw);

	return error ? error : 0;
}