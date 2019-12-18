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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vimc_ent_device {int /*<<< orphan*/  pads; TYPE_1__* ent; } ;
struct v4l2_subdev_ops {int dummy; } ;
struct v4l2_subdev_internal_ops {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  function; } ;
struct v4l2_subdev {TYPE_1__ entity; int /*<<< orphan*/  flags; scalar_t__ ctrl_handler; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; struct v4l2_subdev_internal_ops const* internal_ops; } ;
struct v4l2_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const* const,int) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_1__*) ; 
 int media_entity_pads_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const* const,int) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct vimc_ent_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,struct v4l2_subdev_ops const*) ; 
 int /*<<< orphan*/  vimc_ent_sd_mops ; 
 int /*<<< orphan*/  vimc_pads_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vimc_pads_init (int /*<<< orphan*/ ,unsigned long const*) ; 

int vimc_ent_sd_register(struct vimc_ent_device *ved,
			 struct v4l2_subdev *sd,
			 struct v4l2_device *v4l2_dev,
			 const char *const name,
			 u32 function,
			 u16 num_pads,
			 const unsigned long *pads_flag,
			 const struct v4l2_subdev_internal_ops *sd_int_ops,
			 const struct v4l2_subdev_ops *sd_ops)
{
	int ret;

	/* Allocate the pads */
	ved->pads = vimc_pads_init(num_pads, pads_flag);
	if (IS_ERR(ved->pads))
		return PTR_ERR(ved->pads);

	/* Fill the vimc_ent_device struct */
	ved->ent = &sd->entity;

	/* Initialize the subdev */
	v4l2_subdev_init(sd, sd_ops);
	sd->internal_ops = sd_int_ops;
	sd->entity.function = function;
	sd->entity.ops = &vimc_ent_sd_mops;
	sd->owner = THIS_MODULE;
	strscpy(sd->name, name, sizeof(sd->name));
	v4l2_set_subdevdata(sd, ved);

	/* Expose this subdev to user space */
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	if (sd->ctrl_handler)
		sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS;

	/* Initialize the media entity */
	ret = media_entity_pads_init(&sd->entity, num_pads, ved->pads);
	if (ret)
		goto err_clean_pads;

	/* Register the subdev with the v4l2 and the media framework */
	ret = v4l2_device_register_subdev(v4l2_dev, sd);
	if (ret) {
		dev_err(v4l2_dev->dev,
			"%s: subdev register failed (err=%d)\n",
			name, ret);
		goto err_clean_m_ent;
	}

	return 0;

err_clean_m_ent:
	media_entity_cleanup(&sd->entity);
err_clean_pads:
	vimc_pads_cleanup(ved->pads);
	return ret;
}