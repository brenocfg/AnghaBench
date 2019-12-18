#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_async_subdev {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct imx_media_dev {int /*<<< orphan*/  md; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; } ;
struct TYPE_7__ {int /*<<< orphan*/  function; int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ctrl_handler; struct device* dev; int /*<<< orphan*/  name; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  owner; TYPE_1__ entity; int /*<<< orphan*/ * internal_ops; } ;
struct imx7_csi {scalar_t__ irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl_hdlr; struct imx_media_dev* vdev; TYPE_2__ sd; struct imx_media_dev* imxmd; int /*<<< orphan*/  irqlock; struct imx_media_dev* regbase; struct imx_media_dev* mclk; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMX7_CSI_PAD_SRC ; 
 int /*<<< orphan*/  IMX_MEDIA_GRP_ID_CSI ; 
 scalar_t__ IS_ERR (struct imx_media_dev*) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_VID_IF_BRIDGE ; 
 int PTR_ERR (struct imx_media_dev*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct imx_media_dev* devm_clk_get (struct device*,char*) ; 
 struct imx7_csi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct imx_media_dev* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  imx7_csi_entity_ops ; 
 int /*<<< orphan*/  imx7_csi_internal_ops ; 
 int /*<<< orphan*/  imx7_csi_irq_handler ; 
 int /*<<< orphan*/  imx7_csi_parse_endpoint ; 
 int /*<<< orphan*/  imx7_csi_subdev_ops ; 
 struct imx_media_dev* imx_media_capture_device_init (struct device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_remove (struct imx_media_dev*) ; 
 int /*<<< orphan*/  imx_media_capture_device_unregister (struct imx_media_dev*) ; 
 struct imx_media_dev* imx_media_dev_init (struct device*,int /*<<< orphan*/ *) ; 
 int imx_media_dev_notifier_register (struct imx_media_dev*,int /*<<< orphan*/ *) ; 
 int imx_media_of_add_csi (struct imx_media_dev*,struct device_node*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_fwnode_subdev (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_2__*,struct imx7_csi*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx7_csi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct imx_media_dev *imxmd;
	struct imx7_csi *csi;
	int ret;

	csi = devm_kzalloc(&pdev->dev, sizeof(*csi), GFP_KERNEL);
	if (!csi)
		return -ENOMEM;

	csi->dev = dev;

	csi->mclk = devm_clk_get(&pdev->dev, "mclk");
	if (IS_ERR(csi->mclk)) {
		ret = PTR_ERR(csi->mclk);
		dev_err(dev, "Failed to get mclk: %d", ret);
		return ret;
	}

	csi->irq = platform_get_irq(pdev, 0);
	if (csi->irq < 0)
		return csi->irq;

	csi->regbase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(csi->regbase))
		return PTR_ERR(csi->regbase);

	spin_lock_init(&csi->irqlock);
	mutex_init(&csi->lock);

	/* install interrupt handler */
	ret = devm_request_irq(dev, csi->irq, imx7_csi_irq_handler, 0, "csi",
			       (void *)csi);
	if (ret < 0) {
		dev_err(dev, "Request CSI IRQ failed.\n");
		goto destroy_mutex;
	}

	/* add media device */
	imxmd = imx_media_dev_init(dev, NULL);
	if (IS_ERR(imxmd)) {
		ret = PTR_ERR(imxmd);
		goto destroy_mutex;
	}
	platform_set_drvdata(pdev, &csi->sd);

	ret = imx_media_of_add_csi(imxmd, node);
	if (ret < 0 && ret != -ENODEV && ret != -EEXIST)
		goto cleanup;

	ret = imx_media_dev_notifier_register(imxmd, NULL);
	if (ret < 0)
		goto cleanup;

	csi->imxmd = imxmd;
	v4l2_subdev_init(&csi->sd, &imx7_csi_subdev_ops);
	v4l2_set_subdevdata(&csi->sd, csi);
	csi->sd.internal_ops = &imx7_csi_internal_ops;
	csi->sd.entity.ops = &imx7_csi_entity_ops;
	csi->sd.entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	csi->sd.dev = &pdev->dev;
	csi->sd.owner = THIS_MODULE;
	csi->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	csi->sd.grp_id = IMX_MEDIA_GRP_ID_CSI;
	snprintf(csi->sd.name, sizeof(csi->sd.name), "csi");

	csi->vdev = imx_media_capture_device_init(csi->sd.dev, &csi->sd,
						  IMX7_CSI_PAD_SRC);
	if (IS_ERR(csi->vdev))
		return PTR_ERR(csi->vdev);

	v4l2_ctrl_handler_init(&csi->ctrl_hdlr, 0);
	csi->sd.ctrl_handler = &csi->ctrl_hdlr;

	ret = v4l2_async_register_fwnode_subdev(&csi->sd,
						sizeof(struct v4l2_async_subdev),
						NULL, 0,
						imx7_csi_parse_endpoint);
	if (ret)
		goto free;

	return 0;

free:
	imx_media_capture_device_unregister(csi->vdev);
	imx_media_capture_device_remove(csi->vdev);
	v4l2_ctrl_handler_free(&csi->ctrl_hdlr);

cleanup:
	v4l2_async_notifier_cleanup(&imxmd->notifier);
	v4l2_device_unregister(&imxmd->v4l2_dev);
	media_device_unregister(&imxmd->md);
	media_device_cleanup(&imxmd->md);

destroy_mutex:
	mutex_destroy(&csi->lock);

	return ret;
}