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
struct TYPE_3__ {TYPE_2__* dev; } ;
struct sun6i_csi_dev {TYPE_1__ csi; TYPE_2__* dev; } ;
struct TYPE_4__ {int dma_pfn_offset; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PHYS_OFFSET ; 
 struct sun6i_csi_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sun6i_csi_dev*) ; 
 int sun6i_csi_resource_request (struct sun6i_csi_dev*,struct platform_device*) ; 
 int sun6i_csi_v4l2_init (TYPE_1__*) ; 

__attribute__((used)) static int sun6i_csi_probe(struct platform_device *pdev)
{
	struct sun6i_csi_dev *sdev;
	int ret;

	sdev = devm_kzalloc(&pdev->dev, sizeof(*sdev), GFP_KERNEL);
	if (!sdev)
		return -ENOMEM;

	sdev->dev = &pdev->dev;
	/* The DMA bus has the memory mapped at 0 */
	sdev->dev->dma_pfn_offset = PHYS_OFFSET >> PAGE_SHIFT;

	ret = sun6i_csi_resource_request(sdev, pdev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, sdev);

	sdev->csi.dev = &pdev->dev;
	return sun6i_csi_v4l2_init(&sdev->csi);
}