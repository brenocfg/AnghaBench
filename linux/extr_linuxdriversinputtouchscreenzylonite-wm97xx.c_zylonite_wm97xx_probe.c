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
struct wm97xx {int /*<<< orphan*/  pen_irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  MFP_PIN_GPIO15 ; 
 int /*<<< orphan*/  MFP_PIN_GPIO26 ; 
 int /*<<< orphan*/  WM97XX_GPIO_13 ; 
 int /*<<< orphan*/  WM97XX_GPIO_2 ; 
 int /*<<< orphan*/  WM97XX_GPIO_IN ; 
 int /*<<< orphan*/  WM97XX_GPIO_NOTSTICKY ; 
 int /*<<< orphan*/  WM97XX_GPIO_NOWAKE ; 
 int /*<<< orphan*/  WM97XX_GPIO_OUT ; 
 int /*<<< orphan*/  WM97XX_GPIO_POL_HIGH ; 
 int /*<<< orphan*/  WM97XX_GPIO_STICKY ; 
 int /*<<< orphan*/  WM97XX_GPIO_WAKE ; 
 scalar_t__ cpu_is_pxa320 () ; 
 int /*<<< orphan*/  gpio_to_irq (int) ; 
 int /*<<< orphan*/  irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mfp_to_gpio (int /*<<< orphan*/ ) ; 
 struct wm97xx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm97xx_config_gpio (struct wm97xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm97xx_register_mach_ops (struct wm97xx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zylonite_mach_ops ; 

__attribute__((used)) static int zylonite_wm97xx_probe(struct platform_device *pdev)
{
	struct wm97xx *wm = platform_get_drvdata(pdev);
	int gpio_touch_irq;

	if (cpu_is_pxa320())
		gpio_touch_irq = mfp_to_gpio(MFP_PIN_GPIO15);
	else
		gpio_touch_irq = mfp_to_gpio(MFP_PIN_GPIO26);

	wm->pen_irq = gpio_to_irq(gpio_touch_irq);
	irq_set_irq_type(wm->pen_irq, IRQ_TYPE_EDGE_BOTH);

	wm97xx_config_gpio(wm, WM97XX_GPIO_13, WM97XX_GPIO_IN,
			   WM97XX_GPIO_POL_HIGH,
			   WM97XX_GPIO_STICKY,
			   WM97XX_GPIO_WAKE);
	wm97xx_config_gpio(wm, WM97XX_GPIO_2, WM97XX_GPIO_OUT,
			   WM97XX_GPIO_POL_HIGH,
			   WM97XX_GPIO_NOTSTICKY,
			   WM97XX_GPIO_NOWAKE);

	return wm97xx_register_mach_ops(wm, &zylonite_mach_ops);
}