#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct vsp1_uds {TYPE_1__ entity; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UDS_PAD_SINK ; 
 int /*<<< orphan*/  UDS_PAD_SOURCE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_uds* to_uds (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  uds_try_format (struct vsp1_uds*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uds_set_format(struct v4l2_subdev *subdev,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct vsp1_uds *uds = to_uds(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	mutex_lock(&uds->entity.lock);

	config = vsp1_entity_get_pad_config(&uds->entity, cfg, fmt->which);
	if (!config) {
		ret = -EINVAL;
		goto done;
	}

	uds_try_format(uds, config, fmt->pad, &fmt->format);

	format = vsp1_entity_get_pad_format(&uds->entity, config, fmt->pad);
	*format = fmt->format;

	if (fmt->pad == UDS_PAD_SINK) {
		/* Propagate the format to the source pad. */
		format = vsp1_entity_get_pad_format(&uds->entity, config,
						    UDS_PAD_SOURCE);
		*format = fmt->format;

		uds_try_format(uds, config, UDS_PAD_SOURCE, format);
	}

done:
	mutex_unlock(&uds->entity.lock);
	return ret;
}