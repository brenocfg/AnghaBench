#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {unsigned int pad; int index; int code; } ;
struct v4l2_subdev {int name; } ;
struct smiapp_sensor {int mbus_frame_fmts; int /*<<< orphan*/  mutex; TYPE_2__* internal_csi_format; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int code; } ;
struct TYPE_6__ {int code; } ;
struct TYPE_5__ {struct v4l2_subdev sd; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 unsigned int SMIAPP_PAD_SRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* smiapp_csi_data_formats ; 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int smiapp_enum_mbus_code(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	unsigned int i;
	int idx = -1;
	int rval = -EINVAL;

	mutex_lock(&sensor->mutex);

	dev_err(&client->dev, "subdev %s, pad %d, index %d\n",
		subdev->name, code->pad, code->index);

	if (subdev != &sensor->src->sd || code->pad != SMIAPP_PAD_SRC) {
		if (code->index)
			goto out;

		code->code = sensor->internal_csi_format->code;
		rval = 0;
		goto out;
	}

	for (i = 0; i < ARRAY_SIZE(smiapp_csi_data_formats); i++) {
		if (sensor->mbus_frame_fmts & (1 << i))
			idx++;

		if (idx == code->index) {
			code->code = smiapp_csi_data_formats[i].code;
			dev_err(&client->dev, "found index %d, i %d, code %x\n",
				code->index, i, code->code);
			rval = 0;
			break;
		}
	}

out:
	mutex_unlock(&sensor->mutex);

	return rval;
}