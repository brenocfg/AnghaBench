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
struct stmfts_data {int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  status ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMFTS_READ_STATUS ; 
 struct stmfts_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t stmfts_sysfs_read_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct stmfts_data *sdata = dev_get_drvdata(dev);
	u8 status[4];
	int err;

	err = i2c_smbus_read_i2c_block_data(sdata->client, STMFTS_READ_STATUS,
					    sizeof(status), status);
	if (err)
		return err;

	return sprintf(buf, "%#02x\n", status[0]);
}