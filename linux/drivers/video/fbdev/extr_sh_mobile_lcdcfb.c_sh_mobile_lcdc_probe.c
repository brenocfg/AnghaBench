#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_priv {int irq; struct sh_mobile_lcdc_overlay* overlays; struct sh_mobile_lcdc_chan* ch; int /*<<< orphan*/  base; int /*<<< orphan*/  forced_fourcc; int /*<<< orphan*/  hw_usecnt; TYPE_2__* dev; } ;
struct sh_mobile_lcdc_overlay {struct sh_mobile_lcdc_chan* channel; struct sh_mobile_lcdc_chan* cfg; } ;
struct sh_mobile_lcdc_info {struct sh_mobile_lcdc_chan* overlays; int /*<<< orphan*/  clock_source; struct sh_mobile_lcdc_chan* ch; } ;
struct TYPE_6__ {scalar_t__ max_brightness; } ;
struct sh_mobile_lcdc_chan {int chan; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  reg_offs; int /*<<< orphan*/  enabled; int /*<<< orphan*/  bl; TYPE_1__ bl_info; struct sh_mobile_lcdc_chan* cfg; int /*<<< orphan*/  vsync_completion; int /*<<< orphan*/  frame_end_wait; struct sh_mobile_lcdc_priv* lcdc; int /*<<< orphan*/  open_lock; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {struct sh_mobile_lcdc_info* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sh_mobile_lcdc_chan*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
#define  LCDC_CHAN_MAINLCD 129 
#define  LCDC_CHAN_SUBLCD 128 
 int /*<<< orphan*/  LDCNT2R_ME ; 
 int /*<<< orphan*/  LDCNT2R_SE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sh_mobile_lcdc_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_offs_mainlcd ; 
 int /*<<< orphan*/  lcdc_offs_sublcd ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_bl_probe (TYPE_2__*,struct sh_mobile_lcdc_chan*) ; 
 int sh_mobile_lcdc_channel_fb_register (struct sh_mobile_lcdc_chan*) ; 
 int sh_mobile_lcdc_channel_init (struct sh_mobile_lcdc_chan*) ; 
 int sh_mobile_lcdc_check_interface (struct sh_mobile_lcdc_chan*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_irq ; 
 int sh_mobile_lcdc_overlay_fb_register (struct sh_mobile_lcdc_overlay*) ; 
 int sh_mobile_lcdc_overlay_init (struct sh_mobile_lcdc_overlay*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_remove (struct platform_device*) ; 
 int sh_mobile_lcdc_setup_clocks (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ) ; 
 int sh_mobile_lcdc_start (struct sh_mobile_lcdc_priv*) ; 

__attribute__((used)) static int sh_mobile_lcdc_probe(struct platform_device *pdev)
{
	struct sh_mobile_lcdc_info *pdata = pdev->dev.platform_data;
	struct sh_mobile_lcdc_priv *priv;
	struct resource *res;
	int num_channels;
	int error;
	int irq, i;

	if (!pdata) {
		dev_err(&pdev->dev, "no platform data defined\n");
		return -EINVAL;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platform_get_irq(pdev, 0);
	if (!res || irq < 0) {
		dev_err(&pdev->dev, "cannot get platform resources\n");
		return -ENOENT;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = &pdev->dev;

	for (i = 0; i < ARRAY_SIZE(priv->ch); i++)
		mutex_init(&priv->ch[i].open_lock);
	platform_set_drvdata(pdev, priv);

	error = request_irq(irq, sh_mobile_lcdc_irq, 0,
			    dev_name(&pdev->dev), priv);
	if (error) {
		dev_err(&pdev->dev, "unable to request irq\n");
		goto err1;
	}

	priv->irq = irq;
	atomic_set(&priv->hw_usecnt, -1);

	for (i = 0, num_channels = 0; i < ARRAY_SIZE(pdata->ch); i++) {
		struct sh_mobile_lcdc_chan *ch = priv->ch + num_channels;

		ch->lcdc = priv;
		ch->cfg = &pdata->ch[i];

		error = sh_mobile_lcdc_check_interface(ch);
		if (error) {
			dev_err(&pdev->dev, "unsupported interface type\n");
			goto err1;
		}
		init_waitqueue_head(&ch->frame_end_wait);
		init_completion(&ch->vsync_completion);

		/* probe the backlight is there is one defined */
		if (ch->cfg->bl_info.max_brightness)
			ch->bl = sh_mobile_lcdc_bl_probe(&pdev->dev, ch);

		switch (pdata->ch[i].chan) {
		case LCDC_CHAN_MAINLCD:
			ch->enabled = LDCNT2R_ME;
			ch->reg_offs = lcdc_offs_mainlcd;
			num_channels++;
			break;
		case LCDC_CHAN_SUBLCD:
			ch->enabled = LDCNT2R_SE;
			ch->reg_offs = lcdc_offs_sublcd;
			num_channels++;
			break;
		}
	}

	if (!num_channels) {
		dev_err(&pdev->dev, "no channels defined\n");
		error = -EINVAL;
		goto err1;
	}

	/* for dual channel LCDC (MAIN + SUB) force shared format setting */
	if (num_channels == 2)
		priv->forced_fourcc = pdata->ch[0].fourcc;

	priv->base = ioremap_nocache(res->start, resource_size(res));
	if (!priv->base) {
		error = -ENOMEM;
		goto err1;
	}

	error = sh_mobile_lcdc_setup_clocks(priv, pdata->clock_source);
	if (error) {
		dev_err(&pdev->dev, "unable to setup clocks\n");
		goto err1;
	}

	/* Enable runtime PM. */
	pm_runtime_enable(&pdev->dev);

	for (i = 0; i < num_channels; i++) {
		struct sh_mobile_lcdc_chan *ch = &priv->ch[i];

		error = sh_mobile_lcdc_channel_init(ch);
		if (error)
			goto err1;
	}

	for (i = 0; i < ARRAY_SIZE(pdata->overlays); i++) {
		struct sh_mobile_lcdc_overlay *ovl = &priv->overlays[i];

		ovl->cfg = &pdata->overlays[i];
		ovl->channel = &priv->ch[0];

		error = sh_mobile_lcdc_overlay_init(ovl);
		if (error)
			goto err1;
	}

	error = sh_mobile_lcdc_start(priv);
	if (error) {
		dev_err(&pdev->dev, "unable to start hardware\n");
		goto err1;
	}

	for (i = 0; i < num_channels; i++) {
		struct sh_mobile_lcdc_chan *ch = priv->ch + i;

		error = sh_mobile_lcdc_channel_fb_register(ch);
		if (error)
			goto err1;
	}

	for (i = 0; i < ARRAY_SIZE(pdata->overlays); i++) {
		struct sh_mobile_lcdc_overlay *ovl = &priv->overlays[i];

		error = sh_mobile_lcdc_overlay_fb_register(ovl);
		if (error)
			goto err1;
	}

	return 0;
err1:
	sh_mobile_lcdc_remove(pdev);

	return error;
}