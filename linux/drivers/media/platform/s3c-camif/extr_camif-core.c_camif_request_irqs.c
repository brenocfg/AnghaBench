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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct camif_vp {int /*<<< orphan*/  irq_queue; } ;
struct camif_dev {struct camif_vp* vp; } ;

/* Variables and functions */
 int CAMIF_VP_NUM ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct camif_vp*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  s3c_camif_irq_handler ; 

__attribute__((used)) static int camif_request_irqs(struct platform_device *pdev,
			      struct camif_dev *camif)
{
	int irq, ret, i;

	for (i = 0; i < CAMIF_VP_NUM; i++) {
		struct camif_vp *vp = &camif->vp[i];

		init_waitqueue_head(&vp->irq_queue);

		irq = platform_get_irq(pdev, i);
		if (irq <= 0)
			return -ENXIO;

		ret = devm_request_irq(&pdev->dev, irq, s3c_camif_irq_handler,
				       0, dev_name(&pdev->dev), vp);
		if (ret < 0) {
			dev_err(&pdev->dev, "failed to install IRQ: %d\n", ret);
			break;
		}
	}

	return ret;
}