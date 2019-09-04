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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct mxt_object {scalar_t__ start_address; int num_report_ids; int type; } ;
struct mxt_data {scalar_t__ mem_size; int T5_msg_size; scalar_t__ T5_address; int T6_reportid; scalar_t__ T6_address; scalar_t__ T7_address; scalar_t__ T71_address; int multitouch; int T9_reportid_min; int num_touchids; scalar_t__ T44_address; int T19_reportid; int T100_reportid_min; int T100_reportid_max; int max_reportid; int /*<<< orphan*/  msg_buf; int /*<<< orphan*/  T9_reportid_max; TYPE_1__* info; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int object_num; int family_id; int version; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MXT_GEN_COMMAND_T6 135 
#define  MXT_GEN_MESSAGE_T5 134 
#define  MXT_GEN_POWER_T7 133 
#define  MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71 132 
#define  MXT_SPT_GPIOPWM_T19 131 
#define  MXT_SPT_MESSAGECOUNT_T44 130 
#define  MXT_TOUCH_MULTITOUCHSCREEN_T100 129 
#define  MXT_TOUCH_MULTI_T9 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpus (scalar_t__*) ; 
 int mxt_obj_instances (struct mxt_object*) ; 
 int mxt_obj_size (struct mxt_object*) ; 

__attribute__((used)) static int mxt_parse_object_table(struct mxt_data *data,
				  struct mxt_object *object_table)
{
	struct i2c_client *client = data->client;
	int i;
	u8 reportid;
	u16 end_address;

	/* Valid Report IDs start counting from 1 */
	reportid = 1;
	data->mem_size = 0;
	for (i = 0; i < data->info->object_num; i++) {
		struct mxt_object *object = object_table + i;
		u8 min_id, max_id;

		le16_to_cpus(&object->start_address);

		if (object->num_report_ids) {
			min_id = reportid;
			reportid += object->num_report_ids *
					mxt_obj_instances(object);
			max_id = reportid - 1;
		} else {
			min_id = 0;
			max_id = 0;
		}

		dev_dbg(&data->client->dev,
			"T%u Start:%u Size:%zu Instances:%zu Report IDs:%u-%u\n",
			object->type, object->start_address,
			mxt_obj_size(object), mxt_obj_instances(object),
			min_id, max_id);

		switch (object->type) {
		case MXT_GEN_MESSAGE_T5:
			if (data->info->family_id == 0x80 &&
			    data->info->version < 0x20) {
				/*
				 * On mXT224 firmware versions prior to V2.0
				 * read and discard unused CRC byte otherwise
				 * DMA reads are misaligned.
				 */
				data->T5_msg_size = mxt_obj_size(object);
			} else {
				/* CRC not enabled, so skip last byte */
				data->T5_msg_size = mxt_obj_size(object) - 1;
			}
			data->T5_address = object->start_address;
			break;
		case MXT_GEN_COMMAND_T6:
			data->T6_reportid = min_id;
			data->T6_address = object->start_address;
			break;
		case MXT_GEN_POWER_T7:
			data->T7_address = object->start_address;
			break;
		case MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71:
			data->T71_address = object->start_address;
			break;
		case MXT_TOUCH_MULTI_T9:
			data->multitouch = MXT_TOUCH_MULTI_T9;
			/* Only handle messages from first T9 instance */
			data->T9_reportid_min = min_id;
			data->T9_reportid_max = min_id +
						object->num_report_ids - 1;
			data->num_touchids = object->num_report_ids;
			break;
		case MXT_SPT_MESSAGECOUNT_T44:
			data->T44_address = object->start_address;
			break;
		case MXT_SPT_GPIOPWM_T19:
			data->T19_reportid = min_id;
			break;
		case MXT_TOUCH_MULTITOUCHSCREEN_T100:
			data->multitouch = MXT_TOUCH_MULTITOUCHSCREEN_T100;
			data->T100_reportid_min = min_id;
			data->T100_reportid_max = max_id;
			/* first two report IDs reserved */
			data->num_touchids = object->num_report_ids - 2;
			break;
		}

		end_address = object->start_address
			+ mxt_obj_size(object) * mxt_obj_instances(object) - 1;

		if (end_address >= data->mem_size)
			data->mem_size = end_address + 1;
	}

	/* Store maximum reportid */
	data->max_reportid = reportid;

	/* If T44 exists, T5 position has to be directly after */
	if (data->T44_address && (data->T5_address != data->T44_address + 1)) {
		dev_err(&client->dev, "Invalid T44 position\n");
		return -EINVAL;
	}

	data->msg_buf = kcalloc(data->max_reportid,
				data->T5_msg_size, GFP_KERNEL);
	if (!data->msg_buf)
		return -ENOMEM;

	return 0;
}