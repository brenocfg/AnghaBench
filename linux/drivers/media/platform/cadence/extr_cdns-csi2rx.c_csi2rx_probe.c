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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_4__ entity; int /*<<< orphan*/  name; int /*<<< orphan*/ * dev; int /*<<< orphan*/  owner; } ;
struct csi2rx_priv {int /*<<< orphan*/  notifier; scalar_t__ has_internal_dphy; int /*<<< orphan*/  max_streams; int /*<<< orphan*/  max_lanes; int /*<<< orphan*/  num_lanes; TYPE_1__ subdev; TYPE_5__* pads; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int CSI2RX_PAD_MAX ; 
 size_t CSI2RX_PAD_SINK ; 
 unsigned int CSI2RX_PAD_SOURCE_STREAM0 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEDIA_ENT_F_VID_IF_BRIDGE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_NAME_SIZE ; 
 int csi2rx_get_resources (struct csi2rx_priv*,struct platform_device*) ; 
 int csi2rx_parse_dt (struct csi2rx_priv*) ; 
 int /*<<< orphan*/  csi2rx_subdev_ops ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct csi2rx_priv*) ; 
 struct csi2rx_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (TYPE_4__*,unsigned int,TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct csi2rx_priv*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int csi2rx_probe(struct platform_device *pdev)
{
	struct csi2rx_priv *csi2rx;
	unsigned int i;
	int ret;

	csi2rx = kzalloc(sizeof(*csi2rx), GFP_KERNEL);
	if (!csi2rx)
		return -ENOMEM;
	platform_set_drvdata(pdev, csi2rx);
	csi2rx->dev = &pdev->dev;
	mutex_init(&csi2rx->lock);

	ret = csi2rx_get_resources(csi2rx, pdev);
	if (ret)
		goto err_free_priv;

	ret = csi2rx_parse_dt(csi2rx);
	if (ret)
		goto err_free_priv;

	csi2rx->subdev.owner = THIS_MODULE;
	csi2rx->subdev.dev = &pdev->dev;
	v4l2_subdev_init(&csi2rx->subdev, &csi2rx_subdev_ops);
	v4l2_set_subdevdata(&csi2rx->subdev, &pdev->dev);
	snprintf(csi2rx->subdev.name, V4L2_SUBDEV_NAME_SIZE, "%s.%s",
		 KBUILD_MODNAME, dev_name(&pdev->dev));

	/* Create our media pads */
	csi2rx->subdev.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	csi2rx->pads[CSI2RX_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	for (i = CSI2RX_PAD_SOURCE_STREAM0; i < CSI2RX_PAD_MAX; i++)
		csi2rx->pads[i].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&csi2rx->subdev.entity, CSI2RX_PAD_MAX,
				     csi2rx->pads);
	if (ret)
		goto err_cleanup;

	ret = v4l2_async_register_subdev(&csi2rx->subdev);
	if (ret < 0)
		goto err_cleanup;

	dev_info(&pdev->dev,
		 "Probed CSI2RX with %u/%u lanes, %u streams, %s D-PHY\n",
		 csi2rx->num_lanes, csi2rx->max_lanes, csi2rx->max_streams,
		 csi2rx->has_internal_dphy ? "internal" : "no");

	return 0;

err_cleanup:
	v4l2_async_notifier_cleanup(&csi2rx->notifier);
err_free_priv:
	kfree(csi2rx);
	return ret;
}