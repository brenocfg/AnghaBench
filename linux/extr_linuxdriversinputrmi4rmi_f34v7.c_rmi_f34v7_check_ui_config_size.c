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
struct TYPE_8__ {int ui_config; } ;
struct TYPE_6__ {int size; } ;
struct TYPE_7__ {TYPE_1__ ui_config; } ;
struct TYPE_9__ {int block_size; TYPE_3__ blkcount; TYPE_2__ img; } ;
struct f34_data {int update_size; TYPE_5__* fn; TYPE_4__ v7; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int rmi_f34v7_check_ui_config_size(struct f34_data *f34)
{
	u16 block_count;

	block_count = f34->v7.img.ui_config.size / f34->v7.block_size;
	f34->update_size += block_count;

	if (block_count != f34->v7.blkcount.ui_config) {
		dev_err(&f34->fn->dev, "UI config size mismatch\n");
		return -EINVAL;
	}

	return 0;
}