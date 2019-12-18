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
struct lpc32xx_udc {int /*<<< orphan*/  usb_slv_clk; int /*<<< orphan*/  udca_p_base; int /*<<< orphan*/  udca_v_base; int /*<<< orphan*/  dd_cache; scalar_t__ driver; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  UDCA_BUFF_SIZE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 struct lpc32xx_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pullup (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_debug_file (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  udc_clk_set (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_disable (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_udc_remove(struct platform_device *pdev)
{
	struct lpc32xx_udc *udc = platform_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);
	if (udc->driver)
		return -EBUSY;

	udc_clk_set(udc, 1);
	udc_disable(udc);
	pullup(udc, 0);

	device_init_wakeup(&pdev->dev, 0);
	remove_debug_file(udc);

	dma_pool_destroy(udc->dd_cache);
	dma_free_coherent(&pdev->dev, UDCA_BUFF_SIZE,
			  udc->udca_v_base, udc->udca_p_base);

	clk_disable_unprepare(udc->usb_slv_clk);

	return 0;
}