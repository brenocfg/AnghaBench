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
struct cx231xx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cx231xx_enable_analog_tuner(struct cx231xx *dev)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	struct media_device *mdev = dev->media_dev;
	struct media_entity  *entity, *decoder = NULL, *source;
	struct media_link *link, *found_link = NULL;
	int ret, active_links = 0;

	if (!mdev)
		return 0;

	/*
	 * This will find the tuner that is connected into the decoder.
	 * Technically, this is not 100% correct, as the device may be
	 * using an analog input instead of the tuner. However, as we can't
	 * do DVB streaming while the DMA engine is being used for V4L2,
	 * this should be enough for the actual needs.
	 */
	media_device_for_each_entity(entity, mdev) {
		if (entity->function == MEDIA_ENT_F_ATV_DECODER) {
			decoder = entity;
			break;
		}
	}
	if (!decoder)
		return 0;

	list_for_each_entry(link, &decoder->links, list) {
		if (link->sink->entity == decoder) {
			found_link = link;
			if (link->flags & MEDIA_LNK_FL_ENABLED)
				active_links++;
			break;
		}
	}

	if (active_links == 1 || !found_link)
		return 0;

	source = found_link->source->entity;
	list_for_each_entry(link, &source->links, list) {
		struct media_entity *sink;
		int flags = 0;

		sink = link->sink->entity;

		if (sink == entity)
			flags = MEDIA_LNK_FL_ENABLED;

		ret = media_entity_setup_link(link, flags);
		if (ret) {
			dev_err(dev->dev,
				"Couldn't change link %s->%s to %s. Error %d\n",
				source->name, sink->name,
				flags ? "enabled" : "disabled",
				ret);
			return ret;
		} else
			dev_dbg(dev->dev,
				"link %s->%s was %s\n",
				source->name, sink->name,
				flags ? "ENABLED" : "disabled");
	}
#endif
	return 0;
}