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
struct v4l2_subdev {int name; int /*<<< orphan*/  entity; int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int /*<<< orphan*/  sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct mipid02_dev {struct v4l2_subdev* s_subdev; TYPE_1__ sd; struct i2c_client* i2c_client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_LNK_FL_IMMUTABLE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int media_entity_get_fwnode_pad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mipid02_dev* to_mipid02_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipid02_async_bound(struct v4l2_async_notifier *notifier,
			       struct v4l2_subdev *s_subdev,
			       struct v4l2_async_subdev *asd)
{
	struct mipid02_dev *bridge = to_mipid02_dev(notifier->sd);
	struct i2c_client *client = bridge->i2c_client;
	int source_pad;
	int ret;

	dev_dbg(&client->dev, "sensor_async_bound call %p", s_subdev);

	source_pad = media_entity_get_fwnode_pad(&s_subdev->entity,
						 s_subdev->fwnode,
						 MEDIA_PAD_FL_SOURCE);
	if (source_pad < 0) {
		dev_err(&client->dev, "Couldn't find output pad for subdev %s\n",
			s_subdev->name);
		return source_pad;
	}

	ret = media_create_pad_link(&s_subdev->entity, source_pad,
				    &bridge->sd.entity, 0,
				    MEDIA_LNK_FL_ENABLED |
				    MEDIA_LNK_FL_IMMUTABLE);
	if (ret) {
		dev_err(&client->dev, "Couldn't create media link %d", ret);
		return ret;
	}

	bridge->s_subdev = s_subdev;

	return 0;
}