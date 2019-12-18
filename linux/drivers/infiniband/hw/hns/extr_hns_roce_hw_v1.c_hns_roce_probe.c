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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hns_roce_v1_priv {int dummy; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  priv; struct device* dev; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (unsigned long long) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_dev ; 
 int hns_roce_get_cfg (struct hns_roce_dev*) ; 
 int hns_roce_init (struct hns_roce_dev*) ; 
 struct hns_roce_dev* ib_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dev ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hns_roce_dev*) ; 

__attribute__((used)) static int hns_roce_probe(struct platform_device *pdev)
{
	int ret;
	struct hns_roce_dev *hr_dev;
	struct device *dev = &pdev->dev;

	hr_dev = ib_alloc_device(hns_roce_dev, ib_dev);
	if (!hr_dev)
		return -ENOMEM;

	hr_dev->priv = kzalloc(sizeof(struct hns_roce_v1_priv), GFP_KERNEL);
	if (!hr_dev->priv) {
		ret = -ENOMEM;
		goto error_failed_kzalloc;
	}

	hr_dev->pdev = pdev;
	hr_dev->dev = dev;
	platform_set_drvdata(pdev, hr_dev);

	if (dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64ULL)) &&
	    dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32ULL))) {
		dev_err(dev, "Not usable DMA addressing mode\n");
		ret = -EIO;
		goto error_failed_get_cfg;
	}

	ret = hns_roce_get_cfg(hr_dev);
	if (ret) {
		dev_err(dev, "Get Configuration failed!\n");
		goto error_failed_get_cfg;
	}

	ret = hns_roce_init(hr_dev);
	if (ret) {
		dev_err(dev, "RoCE engine init failed!\n");
		goto error_failed_get_cfg;
	}

	return 0;

error_failed_get_cfg:
	kfree(hr_dev->priv);

error_failed_kzalloc:
	ib_dealloc_device(&hr_dev->ib_dev);

	return ret;
}