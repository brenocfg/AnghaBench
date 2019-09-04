#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_13__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/  owner; int /*<<< orphan*/ * internal_ops; TYPE_4__ entity; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct smiapp_subdev {unsigned short npads; unsigned short source_pad; size_t sink_pad; TYPE_5__ sd; TYPE_3__* pads; TYPE_2__ compose; TYPE_2__* crop; TYPE_8__ sink_fmt; struct smiapp_sensor* sensor; } ;
struct TYPE_9__ {char* name; } ;
struct smiapp_sensor {struct smiapp_subdev* src; struct smiapp_subdev* pixel_array; TYPE_1__ minfo; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int i2c_adapter_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smiapp_entity_ops ; 
 int /*<<< orphan*/  smiapp_get_native_size (struct smiapp_subdev*,TYPE_8__*) ; 
 int /*<<< orphan*/  smiapp_internal_ops ; 
 int /*<<< orphan*/  smiapp_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (TYPE_5__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_5__*,struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smiapp_create_subdev(struct smiapp_sensor *sensor,
				 struct smiapp_subdev *ssd, const char *name,
				 unsigned short num_pads)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);

	if (!ssd)
		return;

	if (ssd != sensor->src)
		v4l2_subdev_init(&ssd->sd, &smiapp_ops);

	ssd->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ssd->sensor = sensor;

	ssd->npads = num_pads;
	ssd->source_pad = num_pads - 1;

	snprintf(ssd->sd.name,
		 sizeof(ssd->sd.name), "%s %s %d-%4.4x", sensor->minfo.name,
		 name, i2c_adapter_id(client->adapter), client->addr);

	smiapp_get_native_size(ssd, &ssd->sink_fmt);

	ssd->compose.width = ssd->sink_fmt.width;
	ssd->compose.height = ssd->sink_fmt.height;
	ssd->crop[ssd->source_pad] = ssd->compose;
	ssd->pads[ssd->source_pad].flags = MEDIA_PAD_FL_SOURCE;
	if (ssd != sensor->pixel_array) {
		ssd->crop[ssd->sink_pad] = ssd->compose;
		ssd->pads[ssd->sink_pad].flags = MEDIA_PAD_FL_SINK;
	}

	ssd->sd.entity.ops = &smiapp_entity_ops;

	if (ssd == sensor->src)
		return;

	ssd->sd.internal_ops = &smiapp_internal_ops;
	ssd->sd.owner = THIS_MODULE;
	ssd->sd.dev = &client->dev;
	v4l2_set_subdevdata(&ssd->sd, client);
}