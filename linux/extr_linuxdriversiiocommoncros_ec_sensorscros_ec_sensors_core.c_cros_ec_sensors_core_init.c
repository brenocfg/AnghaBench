#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_8__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  location; int /*<<< orphan*/  type; } ;
struct ec_response_motion_sense {TYPE_5__ info; } ;
struct ec_params_motion_sense {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  sensor_num; } ;
struct TYPE_10__ {TYPE_3__ info; int /*<<< orphan*/  cmd; } ;
struct cros_ec_sensors_core_state {struct ec_response_motion_sense* resp; int /*<<< orphan*/  loc; int /*<<< orphan*/  type; TYPE_4__ param; TYPE_6__* msg; int /*<<< orphan*/  cmd_lock; TYPE_1__* ec; } ;
struct cros_ec_sensor_platform {int /*<<< orphan*/  sensor_num; } ;
struct cros_ec_dev {scalar_t__ cmd_offset; TYPE_1__* ec_dev; } ;
struct TYPE_12__ {int version; int outsize; scalar_t__ command; scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_response; } ;

/* Variables and functions */
 scalar_t__ EC_CMD_MOTION_SENSE_CMD ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_INFO ; 
 scalar_t__ cros_ec_motion_send_host_cmd (struct cros_ec_sensors_core_state*,int /*<<< orphan*/ ) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_sensor_platform* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 TYPE_6__* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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

	platform_set_drvdata(pdev, indio_dev);

	state->ec = ec->ec_dev;
	state->msg = devm_kzalloc(&pdev->dev,
				max((u16)sizeof(struct ec_params_motion_sense),
				state->ec->max_response), GFP_KERNEL);
	if (!state->msg)
		return -ENOMEM;

	state->resp = (struct ec_response_motion_sense *)state->msg->data;

	mutex_init(&state->cmd_lock);

	/* Set up the host command structure. */
	state->msg->version = 2;
	state->msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	state->msg->outsize = sizeof(struct ec_params_motion_sense);

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->name = pdev->name;

	if (physical_device) {
		indio_dev->modes = INDIO_DIRECT_MODE;

		state->param.cmd = MOTIONSENSE_CMD_INFO;
		state->param.info.sensor_num = sensor_platform->sensor_num;
		if (cros_ec_motion_send_host_cmd(state, 0)) {
			dev_warn(dev, "Can not access sensor info\n");
			return -EIO;
		}
		state->type = state->resp->info.type;
		state->loc = state->resp->info.location;
	}

	return 0;
}