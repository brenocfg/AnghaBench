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
struct bq27xxx_dm_buf {int dirty; int /*<<< orphan*/  data; int /*<<< orphan*/  block; int /*<<< orphan*/  class; } ;
struct bq27xxx_device_info {int opts; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27XXX_DM_BLOCK ; 
 int /*<<< orphan*/  BQ27XXX_DM_CKSUM ; 
 int /*<<< orphan*/  BQ27XXX_DM_CLASS ; 
 int /*<<< orphan*/  BQ27XXX_DM_CTRL ; 
 int /*<<< orphan*/  BQ27XXX_DM_DATA ; 
 int /*<<< orphan*/  BQ27XXX_DM_SZ ; 
 int /*<<< orphan*/  BQ27XXX_MSLEEP (int) ; 
 int BQ27XXX_O_CFGUP ; 
 int /*<<< orphan*/  bq27xxx_battery_checksum_dm_block (struct bq27xxx_dm_buf*) ; 
 int bq27xxx_battery_set_cfgupdate (struct bq27xxx_device_info*) ; 
 int bq27xxx_battery_soft_reset (struct bq27xxx_device_info*) ; 
 int bq27xxx_write (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bq27xxx_write_block (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bq27xxx_battery_write_dm_block(struct bq27xxx_device_info *di,
					  struct bq27xxx_dm_buf *buf)
{
	bool cfgup = di->opts & BQ27XXX_O_CFGUP;
	int ret;

	if (!buf->dirty)
		return 0;

	if (cfgup) {
		ret = bq27xxx_battery_set_cfgupdate(di);
		if (ret < 0)
			return ret;
	}

	ret = bq27xxx_write(di, BQ27XXX_DM_CTRL, 0, true);
	if (ret < 0)
		goto out;

	ret = bq27xxx_write(di, BQ27XXX_DM_CLASS, buf->class, true);
	if (ret < 0)
		goto out;

	ret = bq27xxx_write(di, BQ27XXX_DM_BLOCK, buf->block, true);
	if (ret < 0)
		goto out;

	BQ27XXX_MSLEEP(1);

	ret = bq27xxx_write_block(di, BQ27XXX_DM_DATA, buf->data, BQ27XXX_DM_SZ);
	if (ret < 0)
		goto out;

	ret = bq27xxx_write(di, BQ27XXX_DM_CKSUM,
			    bq27xxx_battery_checksum_dm_block(buf), true);
	if (ret < 0)
		goto out;

	/* DO NOT read BQ27XXX_DM_CKSUM here to verify it! That may cause NVM
	 * corruption on the '425 chip (and perhaps others), which can damage
	 * the chip.
	 */

	if (cfgup) {
		BQ27XXX_MSLEEP(1);
		ret = bq27xxx_battery_soft_reset(di);
		if (ret < 0)
			return ret;
	} else {
		BQ27XXX_MSLEEP(100); /* flash DM updates in <100ms */
	}

	buf->dirty = false;

	return 0;

out:
	if (cfgup)
		bq27xxx_battery_soft_reset(di);

	dev_err(di->dev, "bus error writing chip memory: %d\n", ret);
	return ret;
}