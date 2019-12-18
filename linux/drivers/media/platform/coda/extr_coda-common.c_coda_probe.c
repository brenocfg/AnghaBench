#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct platform_device_id {size_t driver_data; scalar_t__ product; int /*<<< orphan*/  iram_size; scalar_t__ tempbuf_size; scalar_t__ workbuf_size; } ;
struct TYPE_17__ {struct device_node* of_node; struct coda_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {struct platform_device_id* data; } ;
struct gen_pool {int dummy; } ;
struct device_node {int dummy; } ;
struct coda_platform_data {int /*<<< orphan*/  iram_dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct TYPE_16__ {TYPE_14__ blob; int /*<<< orphan*/  dentry; int /*<<< orphan*/  size; scalar_t__ vaddr; int /*<<< orphan*/  paddr; } ;
struct coda_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  workqueue; TYPE_1__ iram; int /*<<< orphan*/  debugfs_root; struct gen_pool* iram_pool; struct platform_device_id* devtype; int /*<<< orphan*/  tempbuf; int /*<<< orphan*/  workbuf; int /*<<< orphan*/  ida; int /*<<< orphan*/  coda_mutex; int /*<<< orphan*/  dev_mutex; void* vdoa; void* rstc; void* regs_base; void* clk_ahb; void* clk_per; TYPE_2__* dev; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 scalar_t__ CODA_DX6 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int) ; 
 int coda_alloc_aux_buf (struct coda_dev*,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 struct platform_device_id* coda_devdata ; 
 int /*<<< orphan*/  coda_dt_ids ; 
 int coda_firmware_request (struct coda_dev*) ; 
 void* coda_get_vdoa_data () ; 
 int /*<<< orphan*/  coda_irq_handler ; 
 int /*<<< orphan*/  debugfs_create_blob (char*,int,int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 struct coda_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct coda_dev*) ; 
 void* devm_reset_control_get_optional_exclusive (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gen_pool_dma_alloc (struct gen_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gen_pool* gen_pool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct gen_pool* of_gen_pool_get (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct coda_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int v4l2_device_register (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coda_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
			of_match_device(of_match_ptr(coda_dt_ids), &pdev->dev);
	const struct platform_device_id *pdev_id;
	struct coda_platform_data *pdata = pdev->dev.platform_data;
	struct device_node *np = pdev->dev.of_node;
	struct gen_pool *pool;
	struct coda_dev *dev;
	int ret, irq;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	pdev_id = of_id ? of_id->data : platform_get_device_id(pdev);

	if (of_id)
		dev->devtype = of_id->data;
	else if (pdev_id)
		dev->devtype = &coda_devdata[pdev_id->driver_data];
	else
		return -EINVAL;

	spin_lock_init(&dev->irqlock);

	dev->dev = &pdev->dev;
	dev->clk_per = devm_clk_get(&pdev->dev, "per");
	if (IS_ERR(dev->clk_per)) {
		dev_err(&pdev->dev, "Could not get per clock\n");
		return PTR_ERR(dev->clk_per);
	}

	dev->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(dev->clk_ahb)) {
		dev_err(&pdev->dev, "Could not get ahb clock\n");
		return PTR_ERR(dev->clk_ahb);
	}

	/* Get  memory for physical registers */
	dev->regs_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(dev->regs_base))
		return PTR_ERR(dev->regs_base);

	/* IRQ */
	irq = platform_get_irq_byname(pdev, "bit");
	if (irq < 0)
		irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "failed to get irq resource\n");
		return irq;
	}

	ret = devm_request_irq(&pdev->dev, irq, coda_irq_handler, 0,
			       dev_name(&pdev->dev), dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to request irq: %d\n", ret);
		return ret;
	}

	dev->rstc = devm_reset_control_get_optional_exclusive(&pdev->dev,
							      NULL);
	if (IS_ERR(dev->rstc)) {
		ret = PTR_ERR(dev->rstc);
		dev_err(&pdev->dev, "failed get reset control: %d\n", ret);
		return ret;
	}

	/* Get IRAM pool from device tree or platform data */
	pool = of_gen_pool_get(np, "iram", 0);
	if (!pool && pdata)
		pool = gen_pool_get(pdata->iram_dev, NULL);
	if (!pool) {
		dev_err(&pdev->dev, "iram pool not available\n");
		return -ENOMEM;
	}
	dev->iram_pool = pool;

	/* Get vdoa_data if supported by the platform */
	dev->vdoa = coda_get_vdoa_data();
	if (PTR_ERR(dev->vdoa) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret)
		return ret;

	mutex_init(&dev->dev_mutex);
	mutex_init(&dev->coda_mutex);
	ida_init(&dev->ida);

	dev->debugfs_root = debugfs_create_dir("coda", NULL);
	if (!dev->debugfs_root)
		dev_warn(&pdev->dev, "failed to create debugfs root\n");

	/* allocate auxiliary per-device buffers for the BIT processor */
	if (dev->devtype->product == CODA_DX6) {
		ret = coda_alloc_aux_buf(dev, &dev->workbuf,
					 dev->devtype->workbuf_size, "workbuf",
					 dev->debugfs_root);
		if (ret < 0)
			goto err_v4l2_register;
	}

	if (dev->devtype->tempbuf_size) {
		ret = coda_alloc_aux_buf(dev, &dev->tempbuf,
					 dev->devtype->tempbuf_size, "tempbuf",
					 dev->debugfs_root);
		if (ret < 0)
			goto err_v4l2_register;
	}

	dev->iram.size = dev->devtype->iram_size;
	dev->iram.vaddr = gen_pool_dma_alloc(dev->iram_pool, dev->iram.size,
					     &dev->iram.paddr);
	if (!dev->iram.vaddr) {
		dev_warn(&pdev->dev, "unable to alloc iram\n");
	} else {
		memset(dev->iram.vaddr, 0, dev->iram.size);
		dev->iram.blob.data = dev->iram.vaddr;
		dev->iram.blob.size = dev->iram.size;
		dev->iram.dentry = debugfs_create_blob("iram", 0644,
						       dev->debugfs_root,
						       &dev->iram.blob);
	}

	dev->workqueue = alloc_workqueue("coda", WQ_UNBOUND | WQ_MEM_RECLAIM, 1);
	if (!dev->workqueue) {
		dev_err(&pdev->dev, "unable to alloc workqueue\n");
		ret = -ENOMEM;
		goto err_v4l2_register;
	}

	platform_set_drvdata(pdev, dev);

	/*
	 * Start activated so we can directly call coda_hw_init in
	 * coda_fw_callback regardless of whether CONFIG_PM is
	 * enabled or whether the device is associated with a PM domain.
	 */
	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = coda_firmware_request(dev);
	if (ret)
		goto err_alloc_workqueue;
	return 0;

err_alloc_workqueue:
	destroy_workqueue(dev->workqueue);
err_v4l2_register:
	v4l2_device_unregister(&dev->v4l2_dev);
	return ret;
}