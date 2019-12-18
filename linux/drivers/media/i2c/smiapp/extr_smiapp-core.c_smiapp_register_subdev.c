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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  entity; } ;
struct smiapp_subdev {TYPE_3__ sd; int /*<<< orphan*/  pads; int /*<<< orphan*/  npads; } ;
struct smiapp_sensor {TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_5__ {TYPE_2__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_device_register_subdev (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_3__*) ; 
 struct i2c_client* v4l2_get_subdevdata (TYPE_2__*) ; 

__attribute__((used)) static int smiapp_register_subdev(struct smiapp_sensor *sensor,
				  struct smiapp_subdev *ssd,
				  struct smiapp_subdev *sink_ssd,
				  u16 source_pad, u16 sink_pad, u32 link_flags)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	int rval;

	if (!sink_ssd)
		return 0;

	rval = media_entity_pads_init(&ssd->sd.entity,
				      ssd->npads, ssd->pads);
	if (rval) {
		dev_err(&client->dev,
			"media_entity_pads_init failed\n");
		return rval;
	}

	rval = v4l2_device_register_subdev(sensor->src->sd.v4l2_dev,
					   &ssd->sd);
	if (rval) {
		dev_err(&client->dev,
			"v4l2_device_register_subdev failed\n");
		return rval;
	}

	rval = media_create_pad_link(&ssd->sd.entity, source_pad,
				     &sink_ssd->sd.entity, sink_pad,
				     link_flags);
	if (rval) {
		dev_err(&client->dev,
			"media_create_pad_link failed\n");
		v4l2_device_unregister_subdev(&ssd->sd);
		return rval;
	}

	return 0;
}