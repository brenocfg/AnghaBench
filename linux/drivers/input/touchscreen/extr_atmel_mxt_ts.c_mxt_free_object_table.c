#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  v4l2; int /*<<< orphan*/  vdev; } ;
struct mxt_data {scalar_t__ max_reportid; scalar_t__ T100_reportid_max; scalar_t__ T100_reportid_min; scalar_t__ T44_address; scalar_t__ T19_reportid; scalar_t__ T9_reportid_max; scalar_t__ T9_reportid_min; scalar_t__ T71_address; scalar_t__ T7_address; scalar_t__ T6_reportid; scalar_t__ T5_msg_size; scalar_t__ T5_address; int /*<<< orphan*/ * msg_buf; int /*<<< orphan*/ * raw_info_block; int /*<<< orphan*/ * info; int /*<<< orphan*/ * object_table; TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxt_free_object_table(struct mxt_data *data)
{
#ifdef CONFIG_TOUCHSCREEN_ATMEL_MXT_T37
	video_unregister_device(&data->dbg.vdev);
	v4l2_device_unregister(&data->dbg.v4l2);
#endif
	data->object_table = NULL;
	data->info = NULL;
	kfree(data->raw_info_block);
	data->raw_info_block = NULL;
	kfree(data->msg_buf);
	data->msg_buf = NULL;
	data->T5_address = 0;
	data->T5_msg_size = 0;
	data->T6_reportid = 0;
	data->T7_address = 0;
	data->T71_address = 0;
	data->T9_reportid_min = 0;
	data->T9_reportid_max = 0;
	data->T19_reportid = 0;
	data->T44_address = 0;
	data->T100_reportid_min = 0;
	data->T100_reportid_max = 0;
	data->max_reportid = 0;
}