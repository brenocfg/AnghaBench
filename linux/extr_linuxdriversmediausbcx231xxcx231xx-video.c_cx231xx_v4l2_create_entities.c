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

void cx231xx_v4l2_create_entities(struct cx231xx *dev)
{
#if defined(CONFIG_MEDIA_CONTROLLER)
	int ret, i;

	/* Create entities for each input connector */
	for (i = 0; i < MAX_CX231XX_INPUT; i++) {
		struct media_entity *ent = &dev->input_ent[i];

		if (!INPUT(i)->type)
			break;

		ent->name = iname[INPUT(i)->type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		switch (INPUT(i)->type) {
		case CX231XX_VMUX_COMPOSITE1:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			break;
		case CX231XX_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			break;
		case CX231XX_VMUX_TELEVISION:
		case CX231XX_VMUX_CABLE:
		case CX231XX_VMUX_DVB:
			/* The DVB core will handle it */
			if (dev->tuner_type == TUNER_ABSENT)
				continue;
			/* fall through */
		default: /* just to shut up a gcc warning */
			ent->function = MEDIA_ENT_F_CONN_RF;
			break;
		}

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (ret < 0)
			pr_err("failed to initialize input pad[%d]!\n", i);

		ret = media_device_register_entity(dev->media_dev, ent);
		if (ret < 0)
			pr_err("failed to register input entity %d!\n", i);
	}
#endif
}