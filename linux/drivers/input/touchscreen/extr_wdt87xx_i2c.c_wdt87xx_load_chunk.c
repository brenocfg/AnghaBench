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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 void* wdt87xx_get_fw_chunk (struct firmware const*,int /*<<< orphan*/ ) ; 
 int wdt87xx_validate_fw_chunk (void const*,int /*<<< orphan*/ ) ; 
 int wdt87xx_write_firmware (struct i2c_client*,void const*) ; 

__attribute__((used)) static int wdt87xx_load_chunk(struct i2c_client *client,
			      const struct firmware *fw, u32 ck_id)
{
	const void *chunk;
	int error;

	chunk = wdt87xx_get_fw_chunk(fw, ck_id);
	if (!chunk) {
		dev_err(&client->dev, "unable to locate chunk (type %d)\n",
			ck_id);
		return -EINVAL;
	}

	error = wdt87xx_validate_fw_chunk(chunk, ck_id);
	if (error) {
		dev_err(&client->dev, "invalid chunk (type %d): %d\n",
			ck_id, error);
		return error;
	}

	error = wdt87xx_write_firmware(client, chunk);
	if (error) {
		dev_err(&client->dev,
			"failed to write fw chunk (type %d): %d\n",
			ck_id, error);
		return error;
	}

	return 0;
}