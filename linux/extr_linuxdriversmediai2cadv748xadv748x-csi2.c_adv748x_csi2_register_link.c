#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  entity; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct adv748x_csi2 {TYPE_1__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CSI2_SINK ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_LNK_FL_IMMUTABLE ; 
 int media_create_pad_link (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,struct v4l2_subdev*) ; 

__attribute__((used)) static int adv748x_csi2_register_link(struct adv748x_csi2 *tx,
				      struct v4l2_device *v4l2_dev,
				      struct v4l2_subdev *src,
				      unsigned int src_pad)
{
	int enabled = MEDIA_LNK_FL_ENABLED;
	int ret;

	/*
	 * Dynamic linking of the AFE is not supported.
	 * Register the links as immutable.
	 */
	enabled |= MEDIA_LNK_FL_IMMUTABLE;

	if (!src->v4l2_dev) {
		ret = v4l2_device_register_subdev(v4l2_dev, src);
		if (ret)
			return ret;
	}

	return media_create_pad_link(&src->entity, src_pad,
				     &tx->sd.entity, ADV748X_CSI2_SINK,
				     enabled);
}