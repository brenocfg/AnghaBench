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
struct v4l2_subdev {int /*<<< orphan*/  entity; TYPE_1__* v4l2_dev; } ;
struct tvp5150 {struct media_pad* input_pad; struct media_entity* input_ent; } ;
struct media_pad {int /*<<< orphan*/  flags; } ;
struct media_entity {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int TVP5150_INPUT_NUM ; 
 int /*<<< orphan*/  TVP5150_PAD_IF_INPUT ; 
 int media_create_pad_link (struct media_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int media_device_register_entity (int /*<<< orphan*/ ,struct media_entity*) ; 
 int /*<<< orphan*/  media_device_unregister_entity (struct media_entity*) ; 
 int media_entity_pads_init (struct media_entity*,int,struct media_pad*) ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_registered(struct v4l2_subdev *sd)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	struct tvp5150 *decoder = to_tvp5150(sd);
	int ret = 0;
	int i;

	for (i = 0; i < TVP5150_INPUT_NUM; i++) {
		struct media_entity *input = &decoder->input_ent[i];
		struct media_pad *pad = &decoder->input_pad[i];

		if (!input->name)
			continue;

		decoder->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		ret = media_entity_pads_init(input, 1, pad);
		if (ret < 0)
			return ret;

		ret = media_device_register_entity(sd->v4l2_dev->mdev, input);
		if (ret < 0)
			return ret;

		ret = media_create_pad_link(input, 0, &sd->entity,
					    TVP5150_PAD_IF_INPUT, 0);
		if (ret < 0) {
			media_device_unregister_entity(input);
			return ret;
		}
	}
#endif

	return 0;
}