#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct lpc32xx_rtc {int irq; TYPE_1__* rtc; int /*<<< orphan*/  lock; TYPE_1__* rtc_base; } ;
struct TYPE_6__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  LPC32XX_RTC_CTRL ; 
 int LPC32XX_RTC_CTRL_CNTR_DIS ; 
 int LPC32XX_RTC_CTRL_MATCH0 ; 
 int LPC32XX_RTC_CTRL_MATCH1 ; 
 int LPC32XX_RTC_CTRL_ONSW_FORCE_HI ; 
 int LPC32XX_RTC_CTRL_ONSW_MATCH0 ; 
 int LPC32XX_RTC_CTRL_ONSW_MATCH1 ; 
 int LPC32XX_RTC_CTRL_SW_RESET ; 
 int /*<<< orphan*/  LPC32XX_RTC_INTSTAT ; 
 int LPC32XX_RTC_INTSTAT_MATCH0 ; 
 int LPC32XX_RTC_INTSTAT_MATCH1 ; 
 int LPC32XX_RTC_INTSTAT_ONSW ; 
 int /*<<< orphan*/  LPC32XX_RTC_KEY ; 
 int LPC32XX_RTC_KEY_ONSW_LOADVAL ; 
 int /*<<< orphan*/  LPC32XX_RTC_MATCH0 ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct lpc32xx_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc32xx_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpc32xx_rtc_alarm_interrupt ; 
 int /*<<< orphan*/  lpc32xx_rtc_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc32xx_rtc*) ; 
 int rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc32xx_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lpc32xx_rtc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct lpc32xx_rtc *rtc;
	int err;
	u32 tmp;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (unlikely(!rtc))
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->rtc_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rtc->rtc_base))
		return PTR_ERR(rtc->rtc_base);

	spin_lock_init(&rtc->lock);

	/*
	 * The RTC is on a separate power domain and can keep it's state
	 * across a chip power cycle. If the RTC has never been previously
	 * setup, then set it up now for the first time.
	 */
	tmp = rtc_readl(rtc, LPC32XX_RTC_CTRL);
	if (rtc_readl(rtc, LPC32XX_RTC_KEY) != LPC32XX_RTC_KEY_ONSW_LOADVAL) {
		tmp &= ~(LPC32XX_RTC_CTRL_SW_RESET |
			LPC32XX_RTC_CTRL_CNTR_DIS |
			LPC32XX_RTC_CTRL_MATCH0 |
			LPC32XX_RTC_CTRL_MATCH1 |
			LPC32XX_RTC_CTRL_ONSW_MATCH0 |
			LPC32XX_RTC_CTRL_ONSW_MATCH1 |
			LPC32XX_RTC_CTRL_ONSW_FORCE_HI);
		rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp);

		/* Clear latched interrupt states */
		rtc_writel(rtc, LPC32XX_RTC_MATCH0, 0xFFFFFFFF);
		rtc_writel(rtc, LPC32XX_RTC_INTSTAT,
			   LPC32XX_RTC_INTSTAT_MATCH0 |
			   LPC32XX_RTC_INTSTAT_MATCH1 |
			   LPC32XX_RTC_INTSTAT_ONSW);

		/* Write key value to RTC so it won't reload on reset */
		rtc_writel(rtc, LPC32XX_RTC_KEY,
			   LPC32XX_RTC_KEY_ONSW_LOADVAL);
	} else {
		rtc_writel(rtc, LPC32XX_RTC_CTRL,
			   tmp & ~LPC32XX_RTC_CTRL_MATCH0);
	}

	platform_set_drvdata(pdev, rtc);

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc))
		return PTR_ERR(rtc->rtc);

	rtc->rtc->ops = &lpc32xx_rtc_ops;
	rtc->rtc->range_max = U32_MAX;

	err = rtc_register_device(rtc->rtc);
	if (err)
		return err;

	/*
	 * IRQ is enabled after device registration in case alarm IRQ
	 * is pending upon suspend exit.
	 */
	rtc->irq = platform_get_irq(pdev, 0);
	if (rtc->irq < 0) {
		dev_warn(&pdev->dev, "Can't get interrupt resource\n");
	} else {
		if (devm_request_irq(&pdev->dev, rtc->irq,
				     lpc32xx_rtc_alarm_interrupt,
				     0, pdev->name, rtc) < 0) {
			dev_warn(&pdev->dev, "Can't request interrupt.\n");
			rtc->irq = -1;
		} else {
			device_init_wakeup(&pdev->dev, 1);
		}
	}

	return 0;
}