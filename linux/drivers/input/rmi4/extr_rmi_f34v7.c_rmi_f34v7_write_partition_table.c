#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {int size; } ;
struct TYPE_9__ {TYPE_3__ bl_config; } ;
struct TYPE_6__ {int bl_config; } ;
struct TYPE_10__ {int config_size; int block_size; int read_config_buf_size; int config_block_count; TYPE_4__ img; scalar_t__ read_config_buf; scalar_t__ config_data; void* config_area; TYPE_1__ blkcount; } ;
struct f34_data {TYPE_5__ v7; TYPE_2__* fn; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int rmi_f34v7_erase_config (struct f34_data*) ; 
 int rmi_f34v7_read_blocks (struct f34_data*,int,int /*<<< orphan*/ ) ; 
 int rmi_f34v7_write_config (struct f34_data*) ; 
 int rmi_f34v7_write_flash_config (struct f34_data*) ; 
 void* v7_BL_CONFIG_AREA ; 
 int /*<<< orphan*/  v7_CMD_READ_CONFIG ; 

__attribute__((used)) static int rmi_f34v7_write_partition_table(struct f34_data *f34)
{
	u16 block_count;
	int ret;

	block_count = f34->v7.blkcount.bl_config;
	f34->v7.config_area = v7_BL_CONFIG_AREA;
	f34->v7.config_size = f34->v7.block_size * block_count;
	devm_kfree(&f34->fn->dev, f34->v7.read_config_buf);
	f34->v7.read_config_buf = devm_kzalloc(&f34->fn->dev,
					       f34->v7.config_size, GFP_KERNEL);
	if (!f34->v7.read_config_buf) {
		f34->v7.read_config_buf_size = 0;
		return -ENOMEM;
	}

	f34->v7.read_config_buf_size = f34->v7.config_size;

	ret = rmi_f34v7_read_blocks(f34, block_count, v7_CMD_READ_CONFIG);
	if (ret < 0)
		return ret;

	ret = rmi_f34v7_erase_config(f34);
	if (ret < 0)
		return ret;

	ret = rmi_f34v7_write_flash_config(f34);
	if (ret < 0)
		return ret;

	f34->v7.config_area = v7_BL_CONFIG_AREA;
	f34->v7.config_data = f34->v7.read_config_buf;
	f34->v7.config_size = f34->v7.img.bl_config.size;
	f34->v7.config_block_count = f34->v7.config_size / f34->v7.block_size;

	ret = rmi_f34v7_write_config(f34);
	if (ret < 0)
		return ret;

	return 0;
}