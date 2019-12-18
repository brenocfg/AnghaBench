#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ ui_firmware; } ;
struct TYPE_6__ {int block_size; TYPE_2__ img; } ;
struct f34_data {TYPE_3__ v7; } ;

/* Variables and functions */
 int rmi_f34v7_write_f34v7_blocks (struct f34_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v7_CMD_WRITE_FW ; 

__attribute__((used)) static int rmi_f34v7_write_firmware(struct f34_data *f34)
{
	u16 blk_count;

	blk_count = f34->v7.img.ui_firmware.size / f34->v7.block_size;

	return rmi_f34v7_write_f34v7_blocks(f34, f34->v7.img.ui_firmware.data,
					    blk_count, v7_CMD_WRITE_FW);
}