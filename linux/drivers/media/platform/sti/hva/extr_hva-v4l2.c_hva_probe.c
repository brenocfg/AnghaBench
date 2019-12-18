#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hva_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  work_queue; TYPE_1__* vdev; int /*<<< orphan*/  lock; struct platform_device* pdev; struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HVA_NAME ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 int /*<<< orphan*/  create_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hva_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_debugfs_create (struct hva_dev*) ; 
 int /*<<< orphan*/  hva_debugfs_remove (struct hva_dev*) ; 
 int hva_hw_probe (struct platform_device*,struct hva_dev*) ; 
 int /*<<< orphan*/  hva_hw_remove (struct hva_dev*) ; 
 int hva_register_device (struct hva_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hva_dev*) ; 
 int /*<<< orphan*/  register_encoders (struct hva_dev*) ; 
 int /*<<< orphan*/  register_formats (struct hva_dev*) ; 
 int v4l2_device_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hva_probe(struct platform_device *pdev)
{
	struct hva_dev *hva;
	struct device *dev = &pdev->dev;
	int ret;

	hva = devm_kzalloc(dev, sizeof(*hva), GFP_KERNEL);
	if (!hva) {
		ret = -ENOMEM;
		goto err;
	}

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	hva->dev = dev;
	hva->pdev = pdev;
	platform_set_drvdata(pdev, hva);

	mutex_init(&hva->lock);

	/* probe hardware */
	ret = hva_hw_probe(pdev, hva);
	if (ret)
		goto err;

	/* register all available encoders */
	register_encoders(hva);

	/* register all supported formats */
	register_formats(hva);

	/* register on V4L2 */
	ret = v4l2_device_register(dev, &hva->v4l2_dev);
	if (ret) {
		dev_err(dev, "%s %s failed to register V4L2 device\n",
			HVA_PREFIX, HVA_NAME);
		goto err_hw;
	}

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_create(hva);
#endif

	hva->work_queue = create_workqueue(HVA_NAME);
	if (!hva->work_queue) {
		dev_err(dev, "%s %s failed to allocate work queue\n",
			HVA_PREFIX, HVA_NAME);
		ret = -ENOMEM;
		goto err_v4l2;
	}

	/* register device */
	ret = hva_register_device(hva);
	if (ret)
		goto err_work_queue;

	dev_info(dev, "%s %s registered as /dev/video%d\n", HVA_PREFIX,
		 HVA_NAME, hva->vdev->num);

	return 0;

err_work_queue:
	destroy_workqueue(hva->work_queue);
err_v4l2:
#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_remove(hva);
#endif
	v4l2_device_unregister(&hva->v4l2_dev);
err_hw:
	hva_hw_remove(hva);
err:
	return ret;
}