#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_9__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_14__ {scalar_t__ max_frequency; scalar_t__ min_frequency; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  location; } ;
struct ec_response_motion_sense {TYPE_6__ info_3; TYPE_5__ info; } ;
struct ec_params_motion_sense {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sensor_num; } ;
struct TYPE_11__ {TYPE_2__ info; int /*<<< orphan*/  cmd; } ;
struct cros_ec_sensors_core_state {struct ec_response_motion_sense* resp; scalar_t__* frequencies; TYPE_7__* msg; TYPE_4__* calib; int /*<<< orphan*/  sign; int /*<<< orphan*/  loc; int /*<<< orphan*/  type; TYPE_3__ param; TYPE_8__* ec; int /*<<< orphan*/  cmd_lock; } ;
struct cros_ec_sensor_platform {int /*<<< orphan*/  sensor_num; } ;
struct cros_ec_dev {scalar_t__ cmd_offset; TYPE_8__* ec_dev; } ;
struct TYPE_16__ {int /*<<< orphan*/  max_response; } ;
struct TYPE_15__ {int version; int outsize; scalar_t__ command; scalar_t__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int CROS_EC_SENSOR_MAX_AXIS ; 
 int CROS_EC_SENSOR_X ; 
 scalar_t__ EC_CMD_MOTION_SENSE_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_INFO ; 
 int /*<<< orphan*/  MOTION_SENSE_DEFAULT_SCALE ; 
 int cros_ec_get_host_cmd_version_mask (TYPE_8__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int cros_ec_motion_send_host_cmd (struct cros_ec_sensors_core_state*,int /*<<< orphan*/ ) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_sensor_platform* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 TYPE_7__* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_default_min_max_freq (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

int cros_ec_sensors_core_init(struct platform_device *pdev,
			      struct iio_dev *indio_dev,
			      bool physical_device)
{
	struct device *dev = &pdev->dev;
	struct cros_ec_sensors_core_state *state = iio_priv(indio_dev);
	struct cros_ec_dev *ec = dev_get_drvdata(pdev->dev.parent);
	struct cros_ec_sensor_platform *sensor_platform = dev_get_platdata(dev);
	u32 ver_mask;
	int ret, i;

	platform_set_drvdata(pdev, indio_dev);

	state->ec = ec->ec_dev;
	state->msg = devm_kzalloc(&pdev->dev,
				max((u16)sizeof(struct ec_params_motion_sense),
				state->ec->max_response), GFP_KERNEL);
	if (!state->msg)
		return -ENOMEM;

	state->resp = (struct ec_response_motion_sense *)state->msg->data;

	mutex_init(&state->cmd_lock);

	ret = cros_ec_get_host_cmd_version_mask(state->ec,
						ec->cmd_offset,
						EC_CMD_MOTION_SENSE_CMD,
						&ver_mask);
	if (ret < 0)
		return ret;

	/* Set up the host command structure. */
	state->msg->version = fls(ver_mask) - 1;
	state->msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	state->msg->outsize = sizeof(struct ec_params_motion_sense);

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->name = pdev->name;

	if (physical_device) {
		indio_dev->modes = INDIO_DIRECT_MODE;

		state->param.cmd = MOTIONSENSE_CMD_INFO;
		state->param.info.sensor_num = sensor_platform->sensor_num;
		ret = cros_ec_motion_send_host_cmd(state, 0);
		if (ret) {
			dev_warn(dev, "Can not access sensor info\n");
			return ret;
		}
		state->type = state->resp->info.type;
		state->loc = state->resp->info.location;

		/* Set sign vector, only used for backward compatibility. */
		memset(state->sign, 1, CROS_EC_SENSOR_MAX_AXIS);

		for (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			state->calib[i].scale = MOTION_SENSE_DEFAULT_SCALE;

		/* 0 is a correct value used to stop the device */
		state->frequencies[0] = 0;
		if (state->msg->version < 3) {
			get_default_min_max_freq(state->resp->info.type,
						 &state->frequencies[1],
						 &state->frequencies[2]);
		} else {
			state->frequencies[1] =
			    state->resp->info_3.min_frequency;
			state->frequencies[2] =
			    state->resp->info_3.max_frequency;
		}
	}

	return 0;
}