#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  entity; struct iss_v4l2_subdevs_group* host_priv; } ;
struct media_entity {int dummy; } ;
struct iss_v4l2_subdevs_group {int interface; scalar_t__ subdevs; } ;
struct iss_platform_data {struct iss_v4l2_subdevs_group* subdevs; } ;
struct TYPE_11__ {TYPE_9__* mdev; } ;
struct TYPE_10__ {struct media_entity entity; } ;
struct TYPE_12__ {TYPE_1__ subdev; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  hw_revision; int /*<<< orphan*/  model; int /*<<< orphan*/  dev; } ;
struct iss_device {TYPE_2__ v4l2_dev; int /*<<< orphan*/  dev; TYPE_7__ csi2b; TYPE_7__ csi2a; int /*<<< orphan*/  resizer; int /*<<< orphan*/  ipipe; int /*<<< orphan*/  ipipeif; TYPE_9__ media_dev; int /*<<< orphan*/  revision; struct iss_platform_data* pdata; } ;

/* Variables and functions */
 unsigned int CSI2_PAD_SINK ; 
 int EINVAL ; 
#define  ISS_INTERFACE_CSI2A_PHY1 129 
#define  ISS_INTERFACE_CSI2B_PHY2 128 
 unsigned int MEDIA_LNK_FL_ENABLED ; 
 unsigned int MEDIA_LNK_FL_IMMUTABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  iss_media_ops ; 
 struct v4l2_subdev* iss_register_subdev_group (struct iss_device*,scalar_t__) ; 
 int /*<<< orphan*/  iss_unregister_entities (struct iss_device*) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct media_entity*,unsigned int,unsigned int) ; 
 int media_device_register (TYPE_9__*) ; 
 int omap4iss_csi2_register_entities (TYPE_7__*,TYPE_2__*) ; 
 int omap4iss_ipipe_register_entities (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int omap4iss_ipipeif_register_entities (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int omap4iss_resizer_register_entities (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int v4l2_device_register_subdev_nodes (TYPE_2__*) ; 

__attribute__((used)) static int iss_register_entities(struct iss_device *iss)
{
	struct iss_platform_data *pdata = iss->pdata;
	struct iss_v4l2_subdevs_group *subdevs;
	int ret;

	iss->media_dev.dev = iss->dev;
	strscpy(iss->media_dev.model, "TI OMAP4 ISS",
		sizeof(iss->media_dev.model));
	iss->media_dev.hw_revision = iss->revision;
	iss->media_dev.ops = &iss_media_ops;
	ret = media_device_register(&iss->media_dev);
	if (ret < 0) {
		dev_err(iss->dev, "Media device registration failed (%d)\n",
			ret);
		return ret;
	}

	iss->v4l2_dev.mdev = &iss->media_dev;
	ret = v4l2_device_register(iss->dev, &iss->v4l2_dev);
	if (ret < 0) {
		dev_err(iss->dev, "V4L2 device registration failed (%d)\n",
			ret);
		goto done;
	}

	/* Register internal entities */
	ret = omap4iss_csi2_register_entities(&iss->csi2a, &iss->v4l2_dev);
	if (ret < 0)
		goto done;

	ret = omap4iss_csi2_register_entities(&iss->csi2b, &iss->v4l2_dev);
	if (ret < 0)
		goto done;

	ret = omap4iss_ipipeif_register_entities(&iss->ipipeif, &iss->v4l2_dev);
	if (ret < 0)
		goto done;

	ret = omap4iss_ipipe_register_entities(&iss->ipipe, &iss->v4l2_dev);
	if (ret < 0)
		goto done;

	ret = omap4iss_resizer_register_entities(&iss->resizer, &iss->v4l2_dev);
	if (ret < 0)
		goto done;

	/* Register external entities */
	for (subdevs = pdata->subdevs; subdevs && subdevs->subdevs; ++subdevs) {
		struct v4l2_subdev *sensor;
		struct media_entity *input;
		unsigned int flags;
		unsigned int pad;

		sensor = iss_register_subdev_group(iss, subdevs->subdevs);
		if (!sensor)
			continue;

		sensor->host_priv = subdevs;

		/* Connect the sensor to the correct interface module.
		 * CSI2a receiver through CSIPHY1, or
		 * CSI2b receiver through CSIPHY2
		 */
		switch (subdevs->interface) {
		case ISS_INTERFACE_CSI2A_PHY1:
			input = &iss->csi2a.subdev.entity;
			pad = CSI2_PAD_SINK;
			flags = MEDIA_LNK_FL_IMMUTABLE
			      | MEDIA_LNK_FL_ENABLED;
			break;

		case ISS_INTERFACE_CSI2B_PHY2:
			input = &iss->csi2b.subdev.entity;
			pad = CSI2_PAD_SINK;
			flags = MEDIA_LNK_FL_IMMUTABLE
			      | MEDIA_LNK_FL_ENABLED;
			break;

		default:
			dev_err(iss->dev, "invalid interface type %u\n",
				subdevs->interface);
			ret = -EINVAL;
			goto done;
		}

		ret = media_create_pad_link(&sensor->entity, 0, input, pad,
					    flags);
		if (ret < 0)
			goto done;
	}

	ret = v4l2_device_register_subdev_nodes(&iss->v4l2_dev);

done:
	if (ret < 0)
		iss_unregister_entities(iss);

	return ret;
}