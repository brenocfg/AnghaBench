#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {TYPE_8__* mdev; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  model; struct device* dev; } ;
struct camss {scalar_t__ version; int csiphy_num; int csid_num; int vfe_num; TYPE_5__ notifier; TYPE_1__ v4l2_dev; void** genpd; struct device* dev; TYPE_8__ media_dev; void* vfe; void* csid; void* csiphy; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ CAMSS_8x16 ; 
 scalar_t__ CAMSS_8x96 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 size_t PM_DOMAIN_VFE0 ; 
 size_t PM_DOMAIN_VFE1 ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int camss_init_subdevices (struct camss*) ; 
 int /*<<< orphan*/  camss_media_ops ; 
 int camss_of_parse_ports (struct camss*) ; 
 int camss_register_entities (struct camss*) ; 
 int /*<<< orphan*/  camss_subdev_notifier_ops ; 
 int /*<<< orphan*/  camss_unregister_entities (struct camss*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* dev_pm_domain_attach_by_id (struct device*,size_t) ; 
 int /*<<< orphan*/  dev_pm_domain_detach (void*,int) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int) ; 
 struct camss* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_init (TYPE_8__*) ; 
 int media_device_register (TYPE_8__*) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct camss*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_5__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_5__*) ; 
 int v4l2_async_notifier_register (TYPE_1__*,TYPE_5__*) ; 
 int v4l2_device_register (struct device*,TYPE_1__*) ; 
 int v4l2_device_register_subdev_nodes (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int camss_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct camss *camss;
	int num_subdevs, ret;

	camss = kzalloc(sizeof(*camss), GFP_KERNEL);
	if (!camss)
		return -ENOMEM;

	atomic_set(&camss->ref_count, 0);
	camss->dev = dev;
	platform_set_drvdata(pdev, camss);

	if (of_device_is_compatible(dev->of_node, "qcom,msm8916-camss")) {
		camss->version = CAMSS_8x16;
		camss->csiphy_num = 2;
		camss->csid_num = 2;
		camss->vfe_num = 1;
	} else if (of_device_is_compatible(dev->of_node,
					   "qcom,msm8996-camss")) {
		camss->version = CAMSS_8x96;
		camss->csiphy_num = 3;
		camss->csid_num = 4;
		camss->vfe_num = 2;
	} else {
		return -EINVAL;
	}

	camss->csiphy = devm_kcalloc(dev, camss->csiphy_num,
				     sizeof(*camss->csiphy), GFP_KERNEL);
	if (!camss->csiphy)
		return -ENOMEM;

	camss->csid = devm_kcalloc(dev, camss->csid_num, sizeof(*camss->csid),
				   GFP_KERNEL);
	if (!camss->csid)
		return -ENOMEM;

	camss->vfe = devm_kcalloc(dev, camss->vfe_num, sizeof(*camss->vfe),
				  GFP_KERNEL);
	if (!camss->vfe)
		return -ENOMEM;

	v4l2_async_notifier_init(&camss->notifier);

	num_subdevs = camss_of_parse_ports(camss);
	if (num_subdevs < 0)
		return num_subdevs;

	ret = camss_init_subdevices(camss);
	if (ret < 0)
		goto err_cleanup;

	ret = dma_set_mask_and_coherent(dev, 0xffffffff);
	if (ret)
		goto err_cleanup;

	camss->media_dev.dev = camss->dev;
	strscpy(camss->media_dev.model, "Qualcomm Camera Subsystem",
		sizeof(camss->media_dev.model));
	camss->media_dev.ops = &camss_media_ops;
	media_device_init(&camss->media_dev);

	camss->v4l2_dev.mdev = &camss->media_dev;
	ret = v4l2_device_register(camss->dev, &camss->v4l2_dev);
	if (ret < 0) {
		dev_err(dev, "Failed to register V4L2 device: %d\n", ret);
		goto err_cleanup;
	}

	ret = camss_register_entities(camss);
	if (ret < 0)
		goto err_register_entities;

	if (num_subdevs) {
		camss->notifier.ops = &camss_subdev_notifier_ops;

		ret = v4l2_async_notifier_register(&camss->v4l2_dev,
						   &camss->notifier);
		if (ret) {
			dev_err(dev,
				"Failed to register async subdev nodes: %d\n",
				ret);
			goto err_register_subdevs;
		}
	} else {
		ret = v4l2_device_register_subdev_nodes(&camss->v4l2_dev);
		if (ret < 0) {
			dev_err(dev, "Failed to register subdev nodes: %d\n",
				ret);
			goto err_register_subdevs;
		}

		ret = media_device_register(&camss->media_dev);
		if (ret < 0) {
			dev_err(dev, "Failed to register media device: %d\n",
				ret);
			goto err_register_subdevs;
		}
	}

	if (camss->version == CAMSS_8x96) {
		camss->genpd[PM_DOMAIN_VFE0] = dev_pm_domain_attach_by_id(
						camss->dev, PM_DOMAIN_VFE0);
		if (IS_ERR(camss->genpd[PM_DOMAIN_VFE0]))
			return PTR_ERR(camss->genpd[PM_DOMAIN_VFE0]);

		camss->genpd[PM_DOMAIN_VFE1] = dev_pm_domain_attach_by_id(
						camss->dev, PM_DOMAIN_VFE1);
		if (IS_ERR(camss->genpd[PM_DOMAIN_VFE1])) {
			dev_pm_domain_detach(camss->genpd[PM_DOMAIN_VFE0],
					     true);
			return PTR_ERR(camss->genpd[PM_DOMAIN_VFE1]);
		}
	}

	pm_runtime_enable(dev);

	return 0;

err_register_subdevs:
	camss_unregister_entities(camss);
err_register_entities:
	v4l2_device_unregister(&camss->v4l2_dev);
err_cleanup:
	v4l2_async_notifier_cleanup(&camss->notifier);

	return ret;
}