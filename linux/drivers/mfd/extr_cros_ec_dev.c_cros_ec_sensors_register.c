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
struct mfd_cell {int version; int outsize; int insize; char* name; int sensor_num; int id; int pdata_size; struct mfd_cell* platform_data; int /*<<< orphan*/  result; scalar_t__ data; scalar_t__ command; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_4__ {int sensor_count; } ;
struct ec_response_motion_sense {TYPE_3__ info; TYPE_1__ dump; } ;
struct TYPE_5__ {int sensor_num; } ;
struct ec_params_motion_sense {TYPE_2__ info; int /*<<< orphan*/  cmd; } ;
struct cros_ec_sensor_platform {int version; int outsize; int insize; char* name; int sensor_num; int id; int pdata_size; struct cros_ec_sensor_platform* platform_data; int /*<<< orphan*/  result; scalar_t__ data; scalar_t__ command; } ;
struct cros_ec_dev {int has_kb_wake_angle; int /*<<< orphan*/  dev; int /*<<< orphan*/  ec_dev; scalar_t__ cmd_offset; } ;
struct cros_ec_command {int version; int outsize; int insize; char* name; int sensor_num; int id; int pdata_size; struct cros_ec_command* platform_data; int /*<<< orphan*/  result; scalar_t__ data; scalar_t__ command; } ;
typedef  int /*<<< orphan*/  sensor_type ;

/* Variables and functions */
 scalar_t__ EC_CMD_MOTION_SENSE_CMD ; 
 int /*<<< orphan*/  EC_FEATURE_MOTION_SENSE_FIFO ; 
 int /*<<< orphan*/  EC_FEATURE_REFINED_TABLET_MODE_HYSTERESIS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_DUMP ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_INFO ; 
#define  MOTIONSENSE_TYPE_ACCEL 134 
#define  MOTIONSENSE_TYPE_ACTIVITY 133 
#define  MOTIONSENSE_TYPE_BARO 132 
#define  MOTIONSENSE_TYPE_GYRO 131 
#define  MOTIONSENSE_TYPE_LIGHT 130 
#define  MOTIONSENSE_TYPE_MAG 129 
 int MOTIONSENSE_TYPE_MAX ; 
#define  MOTIONSENSE_TYPE_PROX 128 
 scalar_t__ cros_ec_check_features (struct cros_ec_dev*,int /*<<< orphan*/ ) ; 
 int cros_ec_cmd_xfer_status (int /*<<< orphan*/ ,struct mfd_cell*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,...) ; 
 struct mfd_cell* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mfd_cell*) ; 
 struct mfd_cell* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ max (int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cros_ec_sensors_register(struct cros_ec_dev *ec)
{
	/*
	 * Issue a command to get the number of sensor reported.
	 * Build an array of sensors driver and register them all.
	 */
	int ret, i, id, sensor_num;
	struct mfd_cell *sensor_cells;
	struct cros_ec_sensor_platform *sensor_platforms;
	int sensor_type[MOTIONSENSE_TYPE_MAX];
	struct ec_params_motion_sense *params;
	struct ec_response_motion_sense *resp;
	struct cros_ec_command *msg;

	msg = kzalloc(sizeof(struct cros_ec_command) +
		      max(sizeof(*params), sizeof(*resp)), GFP_KERNEL);
	if (msg == NULL)
		return;

	msg->version = 2;
	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	msg->outsize = sizeof(*params);
	msg->insize = sizeof(*resp);

	params = (struct ec_params_motion_sense *)msg->data;
	params->cmd = MOTIONSENSE_CMD_DUMP;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	if (ret < 0) {
		dev_warn(ec->dev, "cannot get EC sensor information: %d/%d\n",
			 ret, msg->result);
		goto error;
	}

	resp = (struct ec_response_motion_sense *)msg->data;
	sensor_num = resp->dump.sensor_count;
	/*
	 * Allocate 2 extra sensors if lid angle sensor and/or FIFO are needed.
	 */
	sensor_cells = kcalloc(sensor_num + 2, sizeof(struct mfd_cell),
			       GFP_KERNEL);
	if (sensor_cells == NULL)
		goto error;

	sensor_platforms = kcalloc(sensor_num,
				   sizeof(struct cros_ec_sensor_platform),
				   GFP_KERNEL);
	if (sensor_platforms == NULL)
		goto error_platforms;

	memset(sensor_type, 0, sizeof(sensor_type));
	id = 0;
	for (i = 0; i < sensor_num; i++) {
		params->cmd = MOTIONSENSE_CMD_INFO;
		params->info.sensor_num = i;
		ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
		if (ret < 0) {
			dev_warn(ec->dev, "no info for EC sensor %d : %d/%d\n",
				 i, ret, msg->result);
			continue;
		}
		switch (resp->info.type) {
		case MOTIONSENSE_TYPE_ACCEL:
			sensor_cells[id].name = "cros-ec-accel";
			break;
		case MOTIONSENSE_TYPE_BARO:
			sensor_cells[id].name = "cros-ec-baro";
			break;
		case MOTIONSENSE_TYPE_GYRO:
			sensor_cells[id].name = "cros-ec-gyro";
			break;
		case MOTIONSENSE_TYPE_MAG:
			sensor_cells[id].name = "cros-ec-mag";
			break;
		case MOTIONSENSE_TYPE_PROX:
			sensor_cells[id].name = "cros-ec-prox";
			break;
		case MOTIONSENSE_TYPE_LIGHT:
			sensor_cells[id].name = "cros-ec-light";
			break;
		case MOTIONSENSE_TYPE_ACTIVITY:
			sensor_cells[id].name = "cros-ec-activity";
			break;
		default:
			dev_warn(ec->dev, "unknown type %d\n", resp->info.type);
			continue;
		}
		sensor_platforms[id].sensor_num = i;
		sensor_cells[id].id = sensor_type[resp->info.type];
		sensor_cells[id].platform_data = &sensor_platforms[id];
		sensor_cells[id].pdata_size =
			sizeof(struct cros_ec_sensor_platform);

		sensor_type[resp->info.type]++;
		id++;
	}

	if (sensor_type[MOTIONSENSE_TYPE_ACCEL] >= 2)
		ec->has_kb_wake_angle = true;

	if (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE_FIFO)) {
		sensor_cells[id].name = "cros-ec-ring";
		id++;
	}
	if (cros_ec_check_features(ec,
				EC_FEATURE_REFINED_TABLET_MODE_HYSTERESIS)) {
		sensor_cells[id].name = "cros-ec-lid-angle";
		id++;
	}

	ret = mfd_add_devices(ec->dev, 0, sensor_cells, id,
			      NULL, 0, NULL);
	if (ret)
		dev_err(ec->dev, "failed to add EC sensors\n");

	kfree(sensor_platforms);
error_platforms:
	kfree(sensor_cells);
error:
	kfree(msg);
}