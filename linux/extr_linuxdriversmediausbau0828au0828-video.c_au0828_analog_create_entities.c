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
struct au0828_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void au0828_analog_create_entities(struct au0828_dev *dev)
{
#if defined(CONFIG_MEDIA_CONTROLLER)
	static const char * const inames[] = {
		[AU0828_VMUX_COMPOSITE] = "Composite",
		[AU0828_VMUX_SVIDEO] = "S-Video",
		[AU0828_VMUX_CABLE] = "Cable TV",
		[AU0828_VMUX_TELEVISION] = "Television",
		[AU0828_VMUX_DVB] = "DVB",
	};
	int ret, i;

	/* Initialize Video and VBI pads */
	dev->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vdev.entity, 1, &dev->video_pad);
	if (ret < 0)
		pr_err("failed to initialize video media entity!\n");

	dev->vbi_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dev->vbi_dev.entity, 1, &dev->vbi_pad);
	if (ret < 0)
		pr_err("failed to initialize vbi media entity!\n");

	/* Create entities for each input connector */
	for (i = 0; i < AU0828_MAX_INPUT; i++) {
		struct media_entity *ent = &dev->input_ent[i];

		if (AUVI_INPUT(i).type == AU0828_VMUX_UNDEFINED)
			break;

		ent->name = inames[AUVI_INPUT(i).type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		switch (AUVI_INPUT(i).type) {
		case AU0828_VMUX_COMPOSITE:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			break;
		case AU0828_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			break;
		case AU0828_VMUX_CABLE:
		case AU0828_VMUX_TELEVISION:
		case AU0828_VMUX_DVB:
		default: /* Just to shut up a warning */
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