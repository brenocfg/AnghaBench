#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct soc_device_attribute {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_4__ entity; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * dev; int /*<<< orphan*/  owner; } ;
struct rcar_csi2 {int /*<<< orphan*/  notifier; int /*<<< orphan*/  lanes; int /*<<< orphan*/ * dev; TYPE_1__ subdev; TYPE_5__* pads; scalar_t__ stream_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  info; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 unsigned int NR_OF_RCAR_CSI2_PAD ; 
 size_t RCAR_CSI2_SINK ; 
 unsigned int RCAR_CSI2_SOURCE_VC0 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_NAME_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct rcar_csi2* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (TYPE_4__*,unsigned int,TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_csi2*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8a7795 ; 
 int /*<<< orphan*/  rcar_csi2_entity_ops ; 
 int /*<<< orphan*/  rcar_csi2_subdev_ops ; 
 int rcsi2_parse_dt (struct rcar_csi2*) ; 
 int rcsi2_probe_resources (struct rcar_csi2*,struct platform_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcsi2_probe(struct platform_device *pdev)
{
	const struct soc_device_attribute *attr;
	struct rcar_csi2 *priv;
	unsigned int i;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = of_device_get_match_data(&pdev->dev);

	/*
	 * The different ES versions of r8a7795 (H3) behave differently but
	 * share the same compatible string.
	 */
	attr = soc_device_match(r8a7795);
	if (attr)
		priv->info = attr->data;

	priv->dev = &pdev->dev;

	mutex_init(&priv->lock);
	priv->stream_count = 0;

	ret = rcsi2_probe_resources(priv, pdev);
	if (ret) {
		dev_err(priv->dev, "Failed to get resources\n");
		return ret;
	}

	platform_set_drvdata(pdev, priv);

	ret = rcsi2_parse_dt(priv);
	if (ret)
		return ret;

	priv->subdev.owner = THIS_MODULE;
	priv->subdev.dev = &pdev->dev;
	v4l2_subdev_init(&priv->subdev, &rcar_csi2_subdev_ops);
	v4l2_set_subdevdata(&priv->subdev, &pdev->dev);
	snprintf(priv->subdev.name, V4L2_SUBDEV_NAME_SIZE, "%s %s",
		 KBUILD_MODNAME, dev_name(&pdev->dev));
	priv->subdev.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;

	priv->subdev.entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	priv->subdev.entity.ops = &rcar_csi2_entity_ops;

	priv->pads[RCAR_CSI2_SINK].flags = MEDIA_PAD_FL_SINK;
	for (i = RCAR_CSI2_SOURCE_VC0; i < NR_OF_RCAR_CSI2_PAD; i++)
		priv->pads[i].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&priv->subdev.entity, NR_OF_RCAR_CSI2_PAD,
				     priv->pads);
	if (ret)
		goto error;

	pm_runtime_enable(&pdev->dev);

	ret = v4l2_async_register_subdev(&priv->subdev);
	if (ret < 0)
		goto error;

	dev_info(priv->dev, "%d lanes found\n", priv->lanes);

	return 0;

error:
	v4l2_async_notifier_unregister(&priv->notifier);
	v4l2_async_notifier_cleanup(&priv->notifier);

	return ret;
}