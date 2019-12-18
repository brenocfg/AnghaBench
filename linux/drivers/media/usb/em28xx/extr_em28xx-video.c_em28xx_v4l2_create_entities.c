#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct media_entity {int /*<<< orphan*/  function; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {void* flags; } ;
struct TYPE_7__ {struct media_entity entity; } ;
struct TYPE_6__ {struct media_entity entity; } ;
struct em28xx_v4l2 {TYPE_4__ vbi_pad; TYPE_2__ vbi_dev; TYPE_4__ video_pad; TYPE_1__ vdev; } ;
struct em28xx {TYPE_3__* intf; int /*<<< orphan*/  media_dev; TYPE_4__* input_pad; int /*<<< orphan*/  tuner_type; struct media_entity* input_ent; scalar_t__ is_webcam; struct em28xx_v4l2* v4l2; } ;
struct TYPE_10__ {size_t type; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  EM28XX_VMUX_COMPOSITE 129 
#define  EM28XX_VMUX_SVIDEO 128 
 TYPE_5__* INPUT (int) ; 
 int MAX_EM28XX_INPUT ; 
 int /*<<< orphan*/  MEDIA_ENT_FL_CONNECTOR ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CONN_COMPOSITE ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CONN_RF ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CONN_SVIDEO ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  TUNER_ABSENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ em28xx_vbi_supported (struct em28xx*) ; 
 int /*<<< orphan*/ * iname ; 
 int media_device_register_entity (int /*<<< orphan*/ ,struct media_entity*) ; 
 int media_entity_pads_init (struct media_entity*,int,TYPE_4__*) ; 

__attribute__((used)) static void em28xx_v4l2_create_entities(struct em28xx *dev)
{
#if defined(CONFIG_MEDIA_CONTROLLER)
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	int ret, i;

	/* Initialize Video, VBI and Radio pads */
	v4l2->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&v4l2->vdev.entity, 1, &v4l2->video_pad);
	if (ret < 0)
		dev_err(&dev->intf->dev,
			"failed to initialize video media entity!\n");

	if (em28xx_vbi_supported(dev)) {
		v4l2->vbi_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&v4l2->vbi_dev.entity, 1,
					     &v4l2->vbi_pad);
		if (ret < 0)
			dev_err(&dev->intf->dev,
				"failed to initialize vbi media entity!\n");
	}

	/* Webcams don't have input connectors */
	if (dev->is_webcam)
		return;

	/* Create entities for each input connector */
	for (i = 0; i < MAX_EM28XX_INPUT; i++) {
		struct media_entity *ent = &dev->input_ent[i];

		if (!INPUT(i)->type)
			break;

		ent->name = iname[INPUT(i)->type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		switch (INPUT(i)->type) {
		case EM28XX_VMUX_COMPOSITE:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			break;
		case EM28XX_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			break;
		default: /* EM28XX_VMUX_TELEVISION or EM28XX_RADIO */
			if (dev->tuner_type != TUNER_ABSENT)
				ent->function = MEDIA_ENT_F_CONN_RF;
			break;
		}

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (ret < 0)
			dev_err(&dev->intf->dev,
				"failed to initialize input pad[%d]!\n", i);

		ret = media_device_register_entity(dev->media_dev, ent);
		if (ret < 0)
			dev_err(&dev->intf->dev,
				"failed to register input entity %d!\n", i);
	}
#endif
}