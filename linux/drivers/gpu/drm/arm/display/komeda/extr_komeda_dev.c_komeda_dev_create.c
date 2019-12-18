#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct komeda_product_data {int /*<<< orphan*/  product_id; TYPE_1__* (* identify ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  core_id; } ;
struct komeda_dev {int /*<<< orphan*/ * iommu; TYPE_1__* funcs; struct device* dev; int /*<<< orphan*/  dma_parms; TYPE_2__ chip; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/ * aclk; int /*<<< orphan*/  lock; } ;
struct device {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * dma_parms; } ;
struct TYPE_3__ {int (* enum_resources ) (struct komeda_dev*) ;int (* connect_iommu ) (struct komeda_dev*) ;int /*<<< orphan*/  (* init_format_table ) (struct komeda_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct komeda_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MALIDP_CORE_ID_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MALIDP_CORE_ID_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MALIDP_CORE_ID_PRODUCT_ID (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct komeda_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iommu_get_domain_for_dev (struct device*) ; 
 int komeda_assemble_pipelines (struct komeda_dev*) ; 
 int /*<<< orphan*/  komeda_debugfs_init (struct komeda_dev*) ; 
 int /*<<< orphan*/  komeda_dev_destroy (struct komeda_dev*) ; 
 int komeda_parse_dt (struct device*,struct komeda_dev*) ; 
 int /*<<< orphan*/  komeda_product_match (struct komeda_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_sysfs_attr_group ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct komeda_product_data* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct komeda_dev*) ; 
 int stub3 (struct komeda_dev*) ; 
 int stub4 (struct komeda_dev*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

struct komeda_dev *komeda_dev_create(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	const struct komeda_product_data *product;
	struct komeda_dev *mdev;
	struct resource *io_res;
	int err = 0;

	product = of_device_get_match_data(dev);
	if (!product)
		return ERR_PTR(-ENODEV);

	io_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!io_res) {
		DRM_ERROR("No registers defined.\n");
		return ERR_PTR(-ENODEV);
	}

	mdev = devm_kzalloc(dev, sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return ERR_PTR(-ENOMEM);

	mutex_init(&mdev->lock);

	mdev->dev = dev;
	mdev->reg_base = devm_ioremap_resource(dev, io_res);
	if (IS_ERR(mdev->reg_base)) {
		DRM_ERROR("Map register space failed.\n");
		err = PTR_ERR(mdev->reg_base);
		mdev->reg_base = NULL;
		goto err_cleanup;
	}

	mdev->aclk = devm_clk_get(dev, "aclk");
	if (IS_ERR(mdev->aclk)) {
		DRM_ERROR("Get engine clk failed.\n");
		err = PTR_ERR(mdev->aclk);
		mdev->aclk = NULL;
		goto err_cleanup;
	}

	clk_prepare_enable(mdev->aclk);

	mdev->funcs = product->identify(mdev->reg_base, &mdev->chip);
	if (!komeda_product_match(mdev, product->product_id)) {
		DRM_ERROR("DT configured %x mismatch with real HW %x.\n",
			  product->product_id,
			  MALIDP_CORE_ID_PRODUCT_ID(mdev->chip.core_id));
		err = -ENODEV;
		goto err_cleanup;
	}

	DRM_INFO("Found ARM Mali-D%x version r%dp%d\n",
		 MALIDP_CORE_ID_PRODUCT_ID(mdev->chip.core_id),
		 MALIDP_CORE_ID_MAJOR(mdev->chip.core_id),
		 MALIDP_CORE_ID_MINOR(mdev->chip.core_id));

	mdev->funcs->init_format_table(mdev);

	err = mdev->funcs->enum_resources(mdev);
	if (err) {
		DRM_ERROR("enumerate display resource failed.\n");
		goto err_cleanup;
	}

	err = komeda_parse_dt(dev, mdev);
	if (err) {
		DRM_ERROR("parse device tree failed.\n");
		goto err_cleanup;
	}

	err = komeda_assemble_pipelines(mdev);
	if (err) {
		DRM_ERROR("assemble display pipelines failed.\n");
		goto err_cleanup;
	}

	dev->dma_parms = &mdev->dma_parms;
	dma_set_max_seg_size(dev, DMA_BIT_MASK(32));

	mdev->iommu = iommu_get_domain_for_dev(mdev->dev);
	if (!mdev->iommu)
		DRM_INFO("continue without IOMMU support!\n");

	if (mdev->iommu && mdev->funcs->connect_iommu) {
		err = mdev->funcs->connect_iommu(mdev);
		if (err) {
			mdev->iommu = NULL;
			goto err_cleanup;
		}
	}

	err = sysfs_create_group(&dev->kobj, &komeda_sysfs_attr_group);
	if (err) {
		DRM_ERROR("create sysfs group failed.\n");
		goto err_cleanup;
	}

#ifdef CONFIG_DEBUG_FS
	komeda_debugfs_init(mdev);
#endif

	return mdev;

err_cleanup:
	komeda_dev_destroy(mdev);
	return ERR_PTR(err);
}