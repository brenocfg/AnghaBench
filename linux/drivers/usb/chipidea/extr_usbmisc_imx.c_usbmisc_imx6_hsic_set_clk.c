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
typedef  int u32 ;
struct imx_usbmisc_data {int /*<<< orphan*/  dev; } ;
struct imx_usbmisc {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int MX6_BM_HSIC_CLK_ON ; 
 int MX6_BM_HSIC_EN ; 
 scalar_t__ MX6_USB_HSIC_CTRL_OFFSET ; 
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usbmisc_imx6_hsic_get_reg_offset (struct imx_usbmisc_data*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int usbmisc_imx6_hsic_set_clk(struct imx_usbmisc_data *data, bool on)
{
	unsigned long flags;
	u32 val;
	struct imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	int offset;

	spin_lock_irqsave(&usbmisc->lock, flags);
	offset = usbmisc_imx6_hsic_get_reg_offset(data);
	if (offset < 0) {
		spin_unlock_irqrestore(&usbmisc->lock, flags);
		return offset;
	}

	val = readl(usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET + offset);
	val |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CLK_ON;
	if (on)
		val |= MX6_BM_HSIC_CLK_ON;
	else
		val &= ~MX6_BM_HSIC_CLK_ON;

	writel(val, usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET + offset);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	return 0;
}