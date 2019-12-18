#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct pxafb_mach_info {int num_modes; int /*<<< orphan*/  pxafb_lcd_power; int /*<<< orphan*/  pxafb_backlight_power; scalar_t__ acceleration_enabled; TYPE_6__* modes; } ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_8__ {int /*<<< orphan*/  accel; } ;
struct TYPE_9__ {TYPE_5__ cmap; int /*<<< orphan*/  var; TYPE_1__ fix; } ;
struct TYPE_12__ {int /*<<< orphan*/  notifier_call; } ;
struct pxafb_info {int /*<<< orphan*/  dma_buff_phys; int /*<<< orphan*/ * dma_buff; int /*<<< orphan*/  dma_buff_size; int /*<<< orphan*/  video_mem_size; int /*<<< orphan*/  video_mem; TYPE_2__ fb; TYPE_7__ freq_transition; int /*<<< orphan*/  dev; struct pxafb_info* mmio_base; struct pxafb_info* lcd_supply; int /*<<< orphan*/  lcd_power; int /*<<< orphan*/  backlight_power; } ;
struct pxafb_dma_buff {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {scalar_t__ xres; scalar_t__ yres; scalar_t__ bpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  C_ENABLE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  FB_ACCEL_PXA3XX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct pxafb_info*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct pxafb_mach_info*) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 int PTR_ERR (struct pxafb_info*) ; 
 scalar_t__ cpu_is_pxa3xx () ; 
 int /*<<< orphan*/  cpufreq_register_notifier (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct pxafb_mach_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct pxafb_info* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pxafb_mach_info* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* devm_kmalloc_array (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct pxafb_info* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pxafb_info*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_5__*) ; 
 int /*<<< orphan*/  free_pages_exact (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_options ; 
 struct pxafb_mach_info* of_pxafb_of_mach_info (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pxafb_info*) ; 
 int /*<<< orphan*/  pxafb_check_options (int /*<<< orphan*/ *,struct pxafb_mach_info*) ; 
 int pxafb_check_var (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pxafb_freq_transition ; 
 int /*<<< orphan*/  pxafb_handle_irq ; 
 struct pxafb_info* pxafb_init_fbinfo (int /*<<< orphan*/ *,struct pxafb_mach_info*) ; 
 int pxafb_init_video_memory (struct pxafb_info*) ; 
 int /*<<< orphan*/  pxafb_overlay_init (struct pxafb_info*) ; 
 int pxafb_parse_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pxafb_mach_info*) ; 
 int pxafb_set_par (TYPE_2__*) ; 
 int pxafb_smart_init (struct pxafb_info*) ; 
 int register_framebuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  set_ctrlr_state (struct pxafb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxafb_probe(struct platform_device *dev)
{
	struct pxafb_info *fbi;
	struct pxafb_mach_info *inf, *pdata;
	struct resource *r;
	int i, irq, ret;

	dev_dbg(&dev->dev, "pxafb_probe\n");

	ret = -ENOMEM;
	pdata = dev_get_platdata(&dev->dev);
	inf = devm_kmalloc(&dev->dev, sizeof(*inf), GFP_KERNEL);
	if (!inf)
		goto failed;

	if (pdata) {
		*inf = *pdata;
		inf->modes =
			devm_kmalloc_array(&dev->dev, pdata->num_modes,
					   sizeof(inf->modes[0]), GFP_KERNEL);
		if (!inf->modes)
			goto failed;
		for (i = 0; i < inf->num_modes; i++)
			inf->modes[i] = pdata->modes[i];
	}

	if (!pdata)
		inf = of_pxafb_of_mach_info(&dev->dev);
	if (IS_ERR_OR_NULL(inf))
		goto failed;

	ret = pxafb_parse_options(&dev->dev, g_options, inf);
	if (ret < 0)
		goto failed;

	pxafb_check_options(&dev->dev, inf);

	dev_dbg(&dev->dev, "got a %dx%dx%d LCD\n",
			inf->modes->xres,
			inf->modes->yres,
			inf->modes->bpp);
	if (inf->modes->xres == 0 ||
	    inf->modes->yres == 0 ||
	    inf->modes->bpp == 0) {
		dev_err(&dev->dev, "Invalid resolution or bit depth\n");
		ret = -EINVAL;
		goto failed;
	}

	fbi = pxafb_init_fbinfo(&dev->dev, inf);
	if (IS_ERR(fbi)) {
		dev_err(&dev->dev, "Failed to initialize framebuffer device\n");
		ret = PTR_ERR(fbi);
		goto failed;
	}

	if (cpu_is_pxa3xx() && inf->acceleration_enabled)
		fbi->fb.fix.accel = FB_ACCEL_PXA3XX;

	fbi->backlight_power = inf->pxafb_backlight_power;
	fbi->lcd_power = inf->pxafb_lcd_power;

	fbi->lcd_supply = devm_regulator_get_optional(&dev->dev, "lcd");
	if (IS_ERR(fbi->lcd_supply)) {
		if (PTR_ERR(fbi->lcd_supply) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		fbi->lcd_supply = NULL;
	}

	r = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (r == NULL) {
		dev_err(&dev->dev, "no I/O memory resource defined\n");
		ret = -ENODEV;
		goto failed;
	}

	fbi->mmio_base = devm_ioremap_resource(&dev->dev, r);
	if (IS_ERR(fbi->mmio_base)) {
		dev_err(&dev->dev, "failed to get I/O memory\n");
		ret = -EBUSY;
		goto failed;
	}

	fbi->dma_buff_size = PAGE_ALIGN(sizeof(struct pxafb_dma_buff));
	fbi->dma_buff = dma_alloc_coherent(fbi->dev, fbi->dma_buff_size,
				&fbi->dma_buff_phys, GFP_KERNEL);
	if (fbi->dma_buff == NULL) {
		dev_err(&dev->dev, "failed to allocate memory for DMA\n");
		ret = -ENOMEM;
		goto failed;
	}

	ret = pxafb_init_video_memory(fbi);
	if (ret) {
		dev_err(&dev->dev, "Failed to allocate video RAM: %d\n", ret);
		ret = -ENOMEM;
		goto failed_free_dma;
	}

	irq = platform_get_irq(dev, 0);
	if (irq < 0) {
		dev_err(&dev->dev, "no IRQ defined\n");
		ret = -ENODEV;
		goto failed_free_mem;
	}

	ret = devm_request_irq(&dev->dev, irq, pxafb_handle_irq, 0, "LCD", fbi);
	if (ret) {
		dev_err(&dev->dev, "request_irq failed: %d\n", ret);
		ret = -EBUSY;
		goto failed_free_mem;
	}

	ret = pxafb_smart_init(fbi);
	if (ret) {
		dev_err(&dev->dev, "failed to initialize smartpanel\n");
		goto failed_free_mem;
	}

	/*
	 * This makes sure that our colour bitfield
	 * descriptors are correctly initialised.
	 */
	ret = pxafb_check_var(&fbi->fb.var, &fbi->fb);
	if (ret) {
		dev_err(&dev->dev, "failed to get suitable mode\n");
		goto failed_free_mem;
	}

	ret = pxafb_set_par(&fbi->fb);
	if (ret) {
		dev_err(&dev->dev, "Failed to set parameters\n");
		goto failed_free_mem;
	}

	platform_set_drvdata(dev, fbi);

	ret = register_framebuffer(&fbi->fb);
	if (ret < 0) {
		dev_err(&dev->dev,
			"Failed to register framebuffer device: %d\n", ret);
		goto failed_free_cmap;
	}

	pxafb_overlay_init(fbi);

#ifdef CONFIG_CPU_FREQ
	fbi->freq_transition.notifier_call = pxafb_freq_transition;
	cpufreq_register_notifier(&fbi->freq_transition,
				CPUFREQ_TRANSITION_NOTIFIER);
#endif

	/*
	 * Ok, now enable the LCD controller
	 */
	set_ctrlr_state(fbi, C_ENABLE);

	return 0;

failed_free_cmap:
	if (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);
failed_free_mem:
	free_pages_exact(fbi->video_mem, fbi->video_mem_size);
failed_free_dma:
	dma_free_coherent(&dev->dev, fbi->dma_buff_size,
			fbi->dma_buff, fbi->dma_buff_phys);
failed:
	return ret;
}