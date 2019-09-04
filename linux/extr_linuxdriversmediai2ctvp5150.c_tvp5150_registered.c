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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */

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
					    DEMOD_PAD_IF_INPUT, 0);
		if (ret < 0) {
			media_device_unregister_entity(input);
			return ret;
		}
	}
#endif

	return 0;
}