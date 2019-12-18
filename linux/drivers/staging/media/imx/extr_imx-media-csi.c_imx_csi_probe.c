#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  of_node; struct ipu_client_platformdata* platform_data; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_5__ dev; } ;
struct pinctrl {int dummy; } ;
struct ipu_client_platformdata {scalar_t__ csi; int /*<<< orphan*/  of_node; } ;
struct TYPE_11__ {int /*<<< orphan*/  function; int /*<<< orphan*/ * ops; } ;
struct TYPE_12__ {int flags; int /*<<< orphan*/ * ctrl_handler; TYPE_5__* dev; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; int /*<<< orphan*/  fwnode; TYPE_1__ entity; int /*<<< orphan*/ * internal_ops; } ;
struct csi_priv {scalar_t__ csi_id; int smfc_id; struct pinctrl* vdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl_hdlr; TYPE_5__* dev; TYPE_2__ sd; int /*<<< orphan*/  ipu; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  eof_timeout_timer; int /*<<< orphan*/  active_output_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_SRC_PAD_IDMAC ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMX_MEDIA_GRP_ID_IPU_CSI0 ; 
 int /*<<< orphan*/  IMX_MEDIA_GRP_ID_IPU_CSI1 ; 
 scalar_t__ IS_ERR (struct pinctrl*) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER ; 
 int PTR_ERR (struct pinctrl*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  csi_entity_ops ; 
 int /*<<< orphan*/  csi_idmac_eof_timeout ; 
 int /*<<< orphan*/  csi_internal_ops ; 
 int /*<<< orphan*/  csi_subdev_ops ; 
 int /*<<< orphan*/  dev_dbg (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct csi_priv* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 struct pinctrl* devm_pinctrl_get_select_default (TYPE_5__*) ; 
 int dma_set_coherent_mask (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int imx_csi_async_register (struct csi_priv*) ; 
 struct pinctrl* imx_media_capture_device_init (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_media_capture_device_remove (struct pinctrl*) ; 
 int /*<<< orphan*/  imx_media_grp_id_to_sd_name (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_get_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_2__*,struct csi_priv*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_csi_probe(struct platform_device *pdev)
{
	struct ipu_client_platformdata *pdata;
	struct pinctrl *pinctrl;
	struct csi_priv *priv;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, &priv->sd);
	priv->dev = &pdev->dev;

	ret = dma_set_coherent_mask(priv->dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	/* get parent IPU */
	priv->ipu = dev_get_drvdata(priv->dev->parent);

	/* get our CSI id */
	pdata = priv->dev->platform_data;
	priv->csi_id = pdata->csi;
	priv->smfc_id = (priv->csi_id == 0) ? 0 : 2;

	priv->active_output_pad = CSI_SRC_PAD_IDMAC;

	timer_setup(&priv->eof_timeout_timer, csi_idmac_eof_timeout, 0);
	spin_lock_init(&priv->irqlock);

	v4l2_subdev_init(&priv->sd, &csi_subdev_ops);
	v4l2_set_subdevdata(&priv->sd, priv);
	priv->sd.internal_ops = &csi_internal_ops;
	priv->sd.entity.ops = &csi_entity_ops;
	priv->sd.entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	priv->sd.dev = &pdev->dev;
	priv->sd.fwnode = of_fwnode_handle(pdata->of_node);
	priv->sd.owner = THIS_MODULE;
	priv->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	priv->sd.grp_id = priv->csi_id ?
		IMX_MEDIA_GRP_ID_IPU_CSI1 : IMX_MEDIA_GRP_ID_IPU_CSI0;
	imx_media_grp_id_to_sd_name(priv->sd.name, sizeof(priv->sd.name),
				    priv->sd.grp_id, ipu_get_num(priv->ipu));

	priv->vdev = imx_media_capture_device_init(priv->sd.dev, &priv->sd,
						   CSI_SRC_PAD_IDMAC);
	if (IS_ERR(priv->vdev))
		return PTR_ERR(priv->vdev);

	mutex_init(&priv->lock);

	v4l2_ctrl_handler_init(&priv->ctrl_hdlr, 0);
	priv->sd.ctrl_handler = &priv->ctrl_hdlr;

	/*
	 * The IPUv3 driver did not assign an of_node to this
	 * device. As a result, pinctrl does not automatically
	 * configure our pin groups, so we need to do that manually
	 * here, after setting this device's of_node.
	 */
	priv->dev->of_node = pdata->of_node;
	pinctrl = devm_pinctrl_get_select_default(priv->dev);
	if (IS_ERR(pinctrl)) {
		ret = PTR_ERR(pinctrl);
		dev_dbg(priv->dev,
			"devm_pinctrl_get_select_default() failed: %d\n", ret);
		if (ret != -ENODEV)
			goto free;
	}

	ret = imx_csi_async_register(priv);
	if (ret)
		goto free;

	return 0;
free:
	v4l2_ctrl_handler_free(&priv->ctrl_hdlr);
	mutex_destroy(&priv->lock);
	imx_media_capture_device_remove(priv->vdev);
	return ret;
}