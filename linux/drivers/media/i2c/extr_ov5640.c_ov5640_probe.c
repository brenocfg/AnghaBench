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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_mbus_framefmt {int width; int height; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  code; } ;
struct TYPE_11__ {int /*<<< orphan*/  function; } ;
struct TYPE_10__ {int flags; TYPE_5__ entity; } ;
struct TYPE_9__ {int /*<<< orphan*/  handler; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct ov5640_dev {size_t current_fr; int ae_target; int upside_down; scalar_t__ xclk_freq; TYPE_3__ sd; int /*<<< orphan*/  lock; TYPE_2__ ctrls; TYPE_6__ pad; void* reset_gpio; void* pwdn_gpio; void* xclk; int /*<<< orphan*/  ep; int /*<<< orphan*/ * current_mode; int /*<<< orphan*/ * last_mode; TYPE_1__ frame_interval; struct v4l2_mbus_framefmt fmt; struct i2c_client* i2c_client; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 size_t OV5640_30_FPS ; 
 size_t OV5640_MODE_VGA_640_480 ; 
 scalar_t__ OV5640_XCLK_MAX ; 
 scalar_t__ OV5640_XCLK_MIN ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_MAP_XFER_FUNC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_FULL_RANGE ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 scalar_t__ clk_get_rate (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ov5640_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int fwnode_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_5__*) ; 
 int media_entity_pads_init (TYPE_5__*,int,TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov5640_check_chip_id (struct ov5640_dev*) ; 
 int /*<<< orphan*/ * ov5640_framerates ; 
 int ov5640_get_regulators (struct ov5640_dev*) ; 
 int ov5640_init_controls (struct ov5640_dev*) ; 
 int /*<<< orphan*/ * ov5640_mode_data ; 
 int /*<<< orphan*/  ov5640_subdev_ops ; 
 int v4l2_async_register_subdev_sensor_common (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int v4l2_fwnode_endpoint_parse (struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_3__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5640_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct fwnode_handle *endpoint;
	struct ov5640_dev *sensor;
	struct v4l2_mbus_framefmt *fmt;
	u32 rotation;
	int ret;

	sensor = devm_kzalloc(dev, sizeof(*sensor), GFP_KERNEL);
	if (!sensor)
		return -ENOMEM;

	sensor->i2c_client = client;

	/*
	 * default init sequence initialize sensor to
	 * YUV422 UYVY VGA@30fps
	 */
	fmt = &sensor->fmt;
	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt->colorspace);
	fmt->width = 640;
	fmt->height = 480;
	fmt->field = V4L2_FIELD_NONE;
	sensor->frame_interval.numerator = 1;
	sensor->frame_interval.denominator = ov5640_framerates[OV5640_30_FPS];
	sensor->current_fr = OV5640_30_FPS;
	sensor->current_mode =
		&ov5640_mode_data[OV5640_MODE_VGA_640_480];
	sensor->last_mode = sensor->current_mode;

	sensor->ae_target = 52;

	/* optional indication of physical rotation of sensor */
	ret = fwnode_property_read_u32(dev_fwnode(&client->dev), "rotation",
				       &rotation);
	if (!ret) {
		switch (rotation) {
		case 180:
			sensor->upside_down = true;
			/* fall through */
		case 0:
			break;
		default:
			dev_warn(dev, "%u degrees rotation is not supported, ignoring...\n",
				 rotation);
		}
	}

	endpoint = fwnode_graph_get_next_endpoint(dev_fwnode(&client->dev),
						  NULL);
	if (!endpoint) {
		dev_err(dev, "endpoint node not found\n");
		return -EINVAL;
	}

	ret = v4l2_fwnode_endpoint_parse(endpoint, &sensor->ep);
	fwnode_handle_put(endpoint);
	if (ret) {
		dev_err(dev, "Could not parse endpoint\n");
		return ret;
	}

	/* get system clock (xclk) */
	sensor->xclk = devm_clk_get(dev, "xclk");
	if (IS_ERR(sensor->xclk)) {
		dev_err(dev, "failed to get xclk\n");
		return PTR_ERR(sensor->xclk);
	}

	sensor->xclk_freq = clk_get_rate(sensor->xclk);
	if (sensor->xclk_freq < OV5640_XCLK_MIN ||
	    sensor->xclk_freq > OV5640_XCLK_MAX) {
		dev_err(dev, "xclk frequency out of range: %d Hz\n",
			sensor->xclk_freq);
		return -EINVAL;
	}

	/* request optional power down pin */
	sensor->pwdn_gpio = devm_gpiod_get_optional(dev, "powerdown",
						    GPIOD_OUT_HIGH);
	if (IS_ERR(sensor->pwdn_gpio))
		return PTR_ERR(sensor->pwdn_gpio);

	/* request optional reset pin */
	sensor->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);
	if (IS_ERR(sensor->reset_gpio))
		return PTR_ERR(sensor->reset_gpio);

	v4l2_i2c_subdev_init(&sensor->sd, client, &ov5640_subdev_ops);

	sensor->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
			    V4L2_SUBDEV_FL_HAS_EVENTS;
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	sensor->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sensor->sd.entity, 1, &sensor->pad);
	if (ret)
		return ret;

	ret = ov5640_get_regulators(sensor);
	if (ret)
		return ret;

	mutex_init(&sensor->lock);

	ret = ov5640_check_chip_id(sensor);
	if (ret)
		goto entity_cleanup;

	ret = ov5640_init_controls(sensor);
	if (ret)
		goto entity_cleanup;

	ret = v4l2_async_register_subdev_sensor_common(&sensor->sd);
	if (ret)
		goto free_ctrls;

	return 0;

free_ctrls:
	v4l2_ctrl_handler_free(&sensor->ctrls.handler);
entity_cleanup:
	mutex_destroy(&sensor->lock);
	media_entity_cleanup(&sensor->sd.entity);
	return ret;
}