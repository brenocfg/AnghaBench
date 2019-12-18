#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_priv {scalar_t__ irq; scalar_t__ base; scalar_t__ dot_clk; struct sh_mobile_lcdc_overlay* ch; struct sh_mobile_lcdc_overlay* overlays; } ;
struct sh_mobile_lcdc_overlay {int /*<<< orphan*/  open_lock; scalar_t__ bl; int /*<<< orphan*/  dma_handle; scalar_t__ fb_mem; int /*<<< orphan*/  fb_size; TYPE_5__* cfg; TYPE_1__* tx_dev; } ;
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  open_lock; scalar_t__ bl; int /*<<< orphan*/  dma_handle; scalar_t__ fb_mem; int /*<<< orphan*/  fb_size; TYPE_5__* cfg; TYPE_1__* tx_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_4__* tx_dev; } ;
struct TYPE_8__ {TYPE_2__* driver; } ;
struct TYPE_9__ {TYPE_3__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lcdc; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct sh_mobile_lcdc_overlay*) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct sh_mobile_lcdc_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_bl_remove (scalar_t__) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_channel_fb_cleanup (struct sh_mobile_lcdc_overlay*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_channel_fb_unregister (struct sh_mobile_lcdc_overlay*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_overlay_fb_cleanup (struct sh_mobile_lcdc_overlay*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_overlay_fb_unregister (struct sh_mobile_lcdc_overlay*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_stop (struct sh_mobile_lcdc_priv*) ; 

__attribute__((used)) static int sh_mobile_lcdc_remove(struct platform_device *pdev)
{
	struct sh_mobile_lcdc_priv *priv = platform_get_drvdata(pdev);
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(priv->overlays); i++)
		sh_mobile_lcdc_overlay_fb_unregister(&priv->overlays[i]);
	for (i = 0; i < ARRAY_SIZE(priv->ch); i++)
		sh_mobile_lcdc_channel_fb_unregister(&priv->ch[i]);

	sh_mobile_lcdc_stop(priv);

	for (i = 0; i < ARRAY_SIZE(priv->overlays); i++) {
		struct sh_mobile_lcdc_overlay *ovl = &priv->overlays[i];

		sh_mobile_lcdc_overlay_fb_cleanup(ovl);

		if (ovl->fb_mem)
			dma_free_coherent(&pdev->dev, ovl->fb_size,
					  ovl->fb_mem, ovl->dma_handle);
	}

	for (i = 0; i < ARRAY_SIZE(priv->ch); i++) {
		struct sh_mobile_lcdc_chan *ch = &priv->ch[i];

		if (ch->tx_dev) {
			ch->tx_dev->lcdc = NULL;
			module_put(ch->cfg->tx_dev->dev.driver->owner);
		}

		sh_mobile_lcdc_channel_fb_cleanup(ch);

		if (ch->fb_mem)
			dma_free_coherent(&pdev->dev, ch->fb_size,
					  ch->fb_mem, ch->dma_handle);
	}

	for (i = 0; i < ARRAY_SIZE(priv->ch); i++) {
		struct sh_mobile_lcdc_chan *ch = &priv->ch[i];

		if (ch->bl)
			sh_mobile_lcdc_bl_remove(ch->bl);
		mutex_destroy(&ch->open_lock);
	}

	if (priv->dot_clk) {
		pm_runtime_disable(&pdev->dev);
		clk_put(priv->dot_clk);
	}

	if (priv->base)
		iounmap(priv->base);

	if (priv->irq)
		free_irq(priv->irq, priv);
	kfree(priv);
	return 0;
}