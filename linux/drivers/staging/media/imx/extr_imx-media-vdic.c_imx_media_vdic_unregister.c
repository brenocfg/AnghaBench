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
struct vdic_priv {int /*<<< orphan*/  lock; } ;
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 
 struct vdic_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*) ; 

int imx_media_vdic_unregister(struct v4l2_subdev *sd)
{
	struct vdic_priv *priv = v4l2_get_subdevdata(sd);

	v4l2_info(sd, "Removing\n");

	v4l2_device_unregister_subdev(sd);
	mutex_destroy(&priv->lock);
	media_entity_cleanup(&sd->entity);

	return 0;
}