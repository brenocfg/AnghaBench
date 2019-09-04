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
struct sec_hw_sgl {int dummy; } ;
struct sec_dev_info {int /*<<< orphan*/ * queues; int /*<<< orphan*/  hw_sgl_pool; int /*<<< orphan*/  dev_lock; struct device* dev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SEC_Q_NUM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sec_dev_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_pool_create (char*,struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sec_dev_info*) ; 
 int sec_algs_register () ; 
 int /*<<< orphan*/  sec_algs_unregister () ; 
 int /*<<< orphan*/  sec_base_exit (struct sec_dev_info*) ; 
 int sec_base_init (struct sec_dev_info*,struct platform_device*) ; 
 int sec_id_alloc (struct sec_dev_info*) ; 
 int sec_queue_config (struct sec_dev_info*,int /*<<< orphan*/ *,int) ; 
 int sec_queue_irq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_queue_irq_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_queue_unconfig (struct sec_dev_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sec_probe(struct platform_device *pdev)
{
	struct sec_dev_info *info;
	struct device *dev = &pdev->dev;
	int i, j;
	int ret;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	if (ret) {
		dev_err(dev, "Failed to set 64 bit dma mask %d", ret);
		return -ENODEV;
	}

	info = devm_kzalloc(dev, (sizeof(*info)), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = dev;
	mutex_init(&info->dev_lock);

	info->hw_sgl_pool = dmam_pool_create("sgl", dev,
					     sizeof(struct sec_hw_sgl), 64, 0);
	if (!info->hw_sgl_pool) {
		dev_err(dev, "Failed to create sec sgl dma pool\n");
		return -ENOMEM;
	}

	ret = sec_base_init(info, pdev);
	if (ret) {
		dev_err(dev, "Base initialization fail! %d\n", ret);
		return ret;
	}

	for (i = 0; i < SEC_Q_NUM; i++) {
		ret = sec_queue_config(info, &info->queues[i], i);
		if (ret)
			goto queues_unconfig;

		ret = sec_queue_irq_init(&info->queues[i]);
		if (ret) {
			sec_queue_unconfig(info, &info->queues[i]);
			goto queues_unconfig;
		}
	}

	ret = sec_algs_register();
	if (ret) {
		dev_err(dev, "Failed to register algorithms with crypto %d\n",
			ret);
		goto queues_unconfig;
	}

	platform_set_drvdata(pdev, info);

	ret = sec_id_alloc(info);
	if (ret)
		goto algs_unregister;

	return 0;

algs_unregister:
	sec_algs_unregister();
queues_unconfig:
	for (j = i - 1; j >= 0; j--) {
		sec_queue_irq_uninit(&info->queues[j]);
		sec_queue_unconfig(info, &info->queues[j]);
	}
	sec_base_exit(info);

	return ret;
}