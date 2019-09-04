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
struct fsl_re_drv_private {int total_chans; int /*<<< orphan*/  dma_dev; int /*<<< orphan*/ * re_jrs; } ;

/* Variables and functions */
 struct fsl_re_drv_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_re_remove_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_re_remove(struct platform_device *ofdev)
{
	struct fsl_re_drv_private *re_priv;
	struct device *dev;
	int i;

	dev = &ofdev->dev;
	re_priv = dev_get_drvdata(dev);

	/* Cleanup chan related memory areas */
	for (i = 0; i < re_priv->total_chans; i++)
		fsl_re_remove_chan(re_priv->re_jrs[i]);

	/* Unregister the driver */
	dma_async_device_unregister(&re_priv->dma_dev);

	return 0;
}