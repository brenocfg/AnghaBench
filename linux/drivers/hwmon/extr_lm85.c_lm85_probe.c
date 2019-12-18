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
struct lm85_data {int type; int has_vid5; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  vrm; void* freq_map_size; void* freq_map; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
typedef  enum chips { ____Placeholder_chips } chips ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LM85_REG_VID ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
#define  adm1027 135 
 void* adm1027_freq_map ; 
#define  adt7463 134 
#define  adt7468 133 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct lm85_data*,int /*<<< orphan*/ **) ; 
 struct lm85_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
#define  emc6d100 132 
#define  emc6d102 131 
#define  emc6d103 130 
#define  emc6d103s 129 
 void* lm85_freq_map ; 
 int /*<<< orphan*/  lm85_group ; 
 int /*<<< orphan*/  lm85_group_in4 ; 
 int /*<<< orphan*/  lm85_group_in567 ; 
 int /*<<< orphan*/  lm85_group_minctl ; 
 int /*<<< orphan*/  lm85_group_temp_off ; 
 int /*<<< orphan*/  lm85_init_client (struct i2c_client*) ; 
 int lm85_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
#define  lm96000 128 
 void* lm96000_freq_map ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int lm85_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct lm85_data *data;
	int idx = 0;

	data = devm_kzalloc(dev, sizeof(struct lm85_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	if (client->dev.of_node)
		data->type = (enum chips)of_device_get_match_data(&client->dev);
	else
		data->type = id->driver_data;
	mutex_init(&data->update_lock);

	/* Fill in the chip specific driver values */
	switch (data->type) {
	case adm1027:
	case adt7463:
	case adt7468:
	case emc6d100:
	case emc6d102:
	case emc6d103:
	case emc6d103s:
		data->freq_map = adm1027_freq_map;
		data->freq_map_size = ARRAY_SIZE(adm1027_freq_map);
		break;
	case lm96000:
		data->freq_map = lm96000_freq_map;
		data->freq_map_size = ARRAY_SIZE(lm96000_freq_map);
		break;
	default:
		data->freq_map = lm85_freq_map;
		data->freq_map_size = ARRAY_SIZE(lm85_freq_map);
	}

	/* Set the VRM version */
	data->vrm = vid_which_vrm();

	/* Initialize the LM85 chip */
	lm85_init_client(client);

	/* sysfs hooks */
	data->groups[idx++] = &lm85_group;

	/* minctl and temp_off exist on all chips except emc6d103s */
	if (data->type != emc6d103s) {
		data->groups[idx++] = &lm85_group_minctl;
		data->groups[idx++] = &lm85_group_temp_off;
	}

	/*
	 * The ADT7463/68 have an optional VRM 10 mode where pin 21 is used
	 * as a sixth digital VID input rather than an analog input.
	 */
	if (data->type == adt7463 || data->type == adt7468) {
		u8 vid = lm85_read_value(client, LM85_REG_VID);
		if (vid & 0x80)
			data->has_vid5 = true;
	}

	if (!data->has_vid5)
		data->groups[idx++] = &lm85_group_in4;

	/* The EMC6D100 has 3 additional voltage inputs */
	if (data->type == emc6d100)
		data->groups[idx++] = &lm85_group_in567;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}