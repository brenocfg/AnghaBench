#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_4__ {int /*<<< orphan*/  var; } ;
struct sa1100fb_info {TYPE_3__ freq_transition; int /*<<< orphan*/  map_dma; int /*<<< orphan*/  map_cpu; int /*<<< orphan*/  map_size; int /*<<< orphan*/  dev; TYPE_1__ fb; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHANNON_GPIO_DISP_EN ; 
 int /*<<< orphan*/  cpufreq_register_notifier (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sa1100fb_info*) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_shannon () ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sa1100fb_info*) ; 
 int register_framebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  sa1100fb_check_var (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sa1100fb_freq_transition ; 
 int /*<<< orphan*/  sa1100fb_handle_irq ; 
 struct sa1100fb_info* sa1100fb_init_fbinfo (int /*<<< orphan*/ *) ; 
 int sa1100fb_map_video_memory (struct sa1100fb_info*) ; 

__attribute__((used)) static int sa1100fb_probe(struct platform_device *pdev)
{
	struct sa1100fb_info *fbi;
	struct resource *res;
	int ret, irq;

	if (!dev_get_platdata(&pdev->dev)) {
		dev_err(&pdev->dev, "no platform LCD data\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -EINVAL;

	fbi = sa1100fb_init_fbinfo(&pdev->dev);
	if (!fbi)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	fbi->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(fbi->base))
		return PTR_ERR(fbi->base);

	fbi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(fbi->clk))
		return PTR_ERR(fbi->clk);

	ret = devm_request_irq(&pdev->dev, irq, sa1100fb_handle_irq, 0,
			       "LCD", fbi);
	if (ret) {
		dev_err(&pdev->dev, "request_irq failed: %d\n", ret);
		return ret;
	}

	if (machine_is_shannon()) {
		ret = devm_gpio_request_one(&pdev->dev, SHANNON_GPIO_DISP_EN,
			GPIOF_OUT_INIT_LOW, "display enable");
		if (ret)
			return ret;
	}

	/* Initialize video memory */
	ret = sa1100fb_map_video_memory(fbi);
	if (ret)
		return ret;

	/*
	 * This makes sure that our colour bitfield
	 * descriptors are correctly initialised.
	 */
	sa1100fb_check_var(&fbi->fb.var, &fbi->fb);

	platform_set_drvdata(pdev, fbi);

	ret = register_framebuffer(&fbi->fb);
	if (ret < 0) {
		dma_free_wc(fbi->dev, fbi->map_size, fbi->map_cpu,
			    fbi->map_dma);
		return ret;
	}

#ifdef CONFIG_CPU_FREQ
	fbi->freq_transition.notifier_call = sa1100fb_freq_transition;
	cpufreq_register_notifier(&fbi->freq_transition, CPUFREQ_TRANSITION_NOTIFIER);
#endif

	/* This driver cannot be unloaded at the moment */
	return 0;
}