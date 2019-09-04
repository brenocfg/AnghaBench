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
struct lpc32xx_kscan_drv {int /*<<< orphan*/  kscan_base; int /*<<< orphan*/  clk; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_KS_IRQ (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct lpc32xx_kscan_drv* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_kscan_open(struct input_dev *dev)
{
	struct lpc32xx_kscan_drv *kscandat = input_get_drvdata(dev);
	int error;

	error = clk_prepare_enable(kscandat->clk);
	if (error)
		return error;

	writel(1, LPC32XX_KS_IRQ(kscandat->kscan_base));

	return 0;
}