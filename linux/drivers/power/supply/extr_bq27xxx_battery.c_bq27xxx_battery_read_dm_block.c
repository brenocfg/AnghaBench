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
typedef  scalar_t__ u8 ;
struct bq27xxx_dm_buf {int has_data; int dirty; int /*<<< orphan*/  data; int /*<<< orphan*/  block; int /*<<< orphan*/  class; } ;
struct bq27xxx_device_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27XXX_DM_BLOCK ; 
 int /*<<< orphan*/  BQ27XXX_DM_CKSUM ; 
 int /*<<< orphan*/  BQ27XXX_DM_CLASS ; 
 int /*<<< orphan*/  BQ27XXX_DM_DATA ; 
 int /*<<< orphan*/  BQ27XXX_DM_SZ ; 
 int /*<<< orphan*/  BQ27XXX_MSLEEP (int) ; 
 int EINVAL ; 
 scalar_t__ bq27xxx_battery_checksum_dm_block (struct bq27xxx_dm_buf*) ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 
 int bq27xxx_read_block (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bq27xxx_write (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bq27xxx_battery_read_dm_block(struct bq27xxx_device_info *di,
					 struct bq27xxx_dm_buf *buf)
{
	int ret;

	buf->has_data = false;

	ret = bq27xxx_write(di, BQ27XXX_DM_CLASS, buf->class, true);
	if (ret < 0)
		goto out;

	ret = bq27xxx_write(di, BQ27XXX_DM_BLOCK, buf->block, true);
	if (ret < 0)
		goto out;

	BQ27XXX_MSLEEP(1);

	ret = bq27xxx_read_block(di, BQ27XXX_DM_DATA, buf->data, BQ27XXX_DM_SZ);
	if (ret < 0)
		goto out;

	ret = bq27xxx_read(di, BQ27XXX_DM_CKSUM, true);
	if (ret < 0)
		goto out;

	if ((u8)ret != bq27xxx_battery_checksum_dm_block(buf)) {
		ret = -EINVAL;
		goto out;
	}

	buf->has_data = true;
	buf->dirty = false;

	return 0;

out:
	dev_err(di->dev, "bus error reading chip memory: %d\n", ret);
	return ret;
}