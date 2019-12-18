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
struct omap_drm_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap_drm_private*) ; 
 struct omap_drm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int omapdrm_init (struct omap_drm_private*,int /*<<< orphan*/ *) ; 
 int omapdss_is_initialized () ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_drm_private*) ; 

__attribute__((used)) static int pdev_probe(struct platform_device *pdev)
{
	struct omap_drm_private *priv;
	int ret;

	if (omapdss_is_initialized() == false)
		return -EPROBE_DEFER;

	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_err(&pdev->dev, "Failed to set the DMA mask\n");
		return ret;
	}

	/* Allocate and initialize the driver private structure. */
	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	ret = omapdrm_init(priv, &pdev->dev);
	if (ret < 0)
		kfree(priv);

	return ret;
}