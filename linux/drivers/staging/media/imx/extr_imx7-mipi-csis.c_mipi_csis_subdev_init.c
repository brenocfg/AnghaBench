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
struct v4l2_subdev_ops {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  function; } ;
struct v4l2_subdev {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * internal_ops; TYPE_1__ entity; int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct v4l2_async_subdev {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct csi_state {int index; TYPE_2__ format_mbus; TYPE_3__* csis_fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 char* CSIS_SUBDEV_NAME ; 
 int /*<<< orphan*/  MEDIA_ENT_F_VID_IF_BRIDGE ; 
 int /*<<< orphan*/  MIPI_CSIS_DEF_PIX_HEIGHT ; 
 int /*<<< orphan*/  MIPI_CSIS_DEF_PIX_WIDTH ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mipi_csis_entity_ops ; 
 TYPE_3__* mipi_csis_formats ; 
 int /*<<< orphan*/  mipi_csis_internal_ops ; 
 int /*<<< orphan*/  mipi_csis_parse_endpoint ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int v4l2_async_register_fwnode_subdev (struct v4l2_subdev*,int,unsigned int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,struct v4l2_subdev_ops const*) ; 

__attribute__((used)) static int mipi_csis_subdev_init(struct v4l2_subdev *mipi_sd,
				 struct platform_device *pdev,
				 const struct v4l2_subdev_ops *ops)
{
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	unsigned int sink_port = 0;
	int ret;

	v4l2_subdev_init(mipi_sd, ops);
	mipi_sd->owner = THIS_MODULE;
	snprintf(mipi_sd->name, sizeof(mipi_sd->name), "%s.%d",
		 CSIS_SUBDEV_NAME, state->index);

	mipi_sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	mipi_sd->ctrl_handler = NULL;

	mipi_sd->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	mipi_sd->entity.ops = &mipi_csis_entity_ops;
	mipi_sd->internal_ops = &mipi_csis_internal_ops;

	mipi_sd->dev = &pdev->dev;

	state->csis_fmt = &mipi_csis_formats[0];
	state->format_mbus.code = mipi_csis_formats[0].code;
	state->format_mbus.width = MIPI_CSIS_DEF_PIX_WIDTH;
	state->format_mbus.height = MIPI_CSIS_DEF_PIX_HEIGHT;
	state->format_mbus.field = V4L2_FIELD_NONE;

	v4l2_set_subdevdata(mipi_sd, &pdev->dev);

	ret = v4l2_async_register_fwnode_subdev(mipi_sd,
						sizeof(struct v4l2_async_subdev),
						&sink_port, 1,
						mipi_csis_parse_endpoint);
	if (ret < 0)
		dev_err(&pdev->dev, "async fwnode register failed: %d\n", ret);

	return ret;
}