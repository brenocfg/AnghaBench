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
struct lpc32xx_kscan_drv {int /*<<< orphan*/  clk; int /*<<< orphan*/  kscan_base; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_KS_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct lpc32xx_kscan_drv* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_kscan_close(struct input_dev *dev)
{
	struct lpc32xx_kscan_drv *kscandat = input_get_drvdata(dev);

	writel(1, LPC32XX_KS_IRQ(kscandat->kscan_base));
	clk_disable_unprepare(kscandat->clk);
}