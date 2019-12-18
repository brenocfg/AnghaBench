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
struct fts_data {int /*<<< orphan*/  access_lock; } ;

/* Variables and functions */
 unsigned short FTS_PAGE_SELECT_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned short,...) ; 
 struct fts_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts_write_byte(struct i2c_client *client, unsigned short reg,
			  unsigned char value)
{
	int ret;
	unsigned char page = reg >> 8;
	struct fts_data *data = dev_get_drvdata(&client->dev);

	mutex_lock(&data->access_lock);

	dev_dbg(&client->dev, "page select - page: 0x%.02x\n", page);
	ret = i2c_smbus_write_byte_data(client, FTS_PAGE_SELECT_REG, page);
	if (ret < 0)
		goto error;

	reg &= 0xFF;
	dev_dbg(&client->dev,
		"write - reg: 0x%.02x: val: 0x%.02x\n", reg, value);
	ret = i2c_smbus_write_byte_data(client, reg, value);

error:
	mutex_unlock(&data->access_lock);
	return ret;
}