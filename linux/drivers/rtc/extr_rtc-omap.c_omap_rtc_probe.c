#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct resource {int dummy; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct TYPE_35__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_6__ dev; } ;
struct omap_rtc {int is_pmic_controller; scalar_t__ irq_timer; scalar_t__ irq_alarm; int has_ext_clk; TYPE_1__* type; TYPE_2__* clk; TYPE_2__* pctldev; TYPE_2__* rtc; TYPE_2__* base; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_34__ {struct omap_rtc* priv; } ;
struct TYPE_33__ {int /*<<< orphan*/  name; } ;
struct TYPE_32__ {TYPE_6__ dev; int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; int /*<<< orphan*/ * ops; } ;
struct TYPE_31__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;scalar_t__ has_power_up_reset; scalar_t__ has_pmic_mode; scalar_t__ has_32kclk_en; int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int OMAP_RTC_CTRL_AUTO_COMP ; 
 int /*<<< orphan*/  OMAP_RTC_CTRL_REG ; 
 int OMAP_RTC_CTRL_SPLIT ; 
 int OMAP_RTC_CTRL_STOP ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_REG ; 
 int OMAP_RTC_OSC_32KCLK_EN ; 
 int OMAP_RTC_OSC_OSC32K_GZ_DISABLE ; 
 int /*<<< orphan*/  OMAP_RTC_OSC_REG ; 
 int OMAP_RTC_OSC_SEL_32KCLK_SRC ; 
 int OMAP_RTC_STATUS_ALARM ; 
 int OMAP_RTC_STATUS_ALARM2 ; 
 int OMAP_RTC_STATUS_POWER_UP ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_2000 ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_END_2099 ; 
 int /*<<< orphan*/  clk_disable_unprepare (TYPE_2__*) ; 
 int /*<<< orphan*/  clk_prepare_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_6__*,int) ; 
 void* devm_clk_get (TYPE_6__*,char*) ; 
 TYPE_2__* devm_ioremap_resource (TYPE_6__*,struct resource*) ; 
 struct omap_rtc* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_rtc*) ; 
 TYPE_2__* devm_rtc_allocate_device (TYPE_6__*) ; 
 scalar_t__ of_device_is_system_power_controller (int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_5__ omap_rtc_nvmem_config ; 
 int /*<<< orphan*/  omap_rtc_of_match ; 
 int /*<<< orphan*/  omap_rtc_ops ; 
 scalar_t__ omap_rtc_power_off ; 
 struct omap_rtc* omap_rtc_power_off_rtc ; 
 TYPE_2__* pinctrl_register (TYPE_3__*,TYPE_6__*,struct omap_rtc*) ; 
 int /*<<< orphan*/  pinctrl_unregister (TYPE_2__*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_rtc*) ; 
 scalar_t__ pm_power_off ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_6__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_6__*) ; 
 int /*<<< orphan*/  rtc_irq ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_2__*,TYPE_5__*) ; 
 TYPE_3__ rtc_pinctrl_desc ; 
 int rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int rtc_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rtc_write (struct omap_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_writel (struct omap_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub3 (struct omap_rtc*) ; 

__attribute__((used)) static int omap_rtc_probe(struct platform_device *pdev)
{
	struct omap_rtc	*rtc;
	struct resource	*res;
	u8 reg, mask, new_ctrl;
	const struct platform_device_id *id_entry;
	const struct of_device_id *of_id;
	int ret;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	of_id = of_match_device(omap_rtc_of_match, &pdev->dev);
	if (of_id) {
		rtc->type = of_id->data;
		rtc->is_pmic_controller = rtc->type->has_pmic_mode &&
			of_device_is_system_power_controller(pdev->dev.of_node);
	} else {
		id_entry = platform_get_device_id(pdev);
		rtc->type = (void *)id_entry->driver_data;
	}

	rtc->irq_timer = platform_get_irq(pdev, 0);
	if (rtc->irq_timer <= 0)
		return -ENOENT;

	rtc->irq_alarm = platform_get_irq(pdev, 1);
	if (rtc->irq_alarm <= 0)
		return -ENOENT;

	rtc->clk = devm_clk_get(&pdev->dev, "ext-clk");
	if (!IS_ERR(rtc->clk))
		rtc->has_ext_clk = true;
	else
		rtc->clk = devm_clk_get(&pdev->dev, "int-clk");

	if (!IS_ERR(rtc->clk))
		clk_prepare_enable(rtc->clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rtc->base)) {
		clk_disable_unprepare(rtc->clk);
		return PTR_ERR(rtc->base);
	}

	platform_set_drvdata(pdev, rtc);

	/* Enable the clock/module so that we can access the registers */
	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	rtc->type->unlock(rtc);

	/*
	 * disable interrupts
	 *
	 * NOTE: ALARM2 is not cleared on AM3352 if rtc_write (writeb) is used
	 */
	rtc_writel(rtc, OMAP_RTC_INTERRUPTS_REG, 0);

	/* enable RTC functional clock */
	if (rtc->type->has_32kclk_en) {
		reg = rtc_read(rtc, OMAP_RTC_OSC_REG);
		rtc_writel(rtc, OMAP_RTC_OSC_REG,
				reg | OMAP_RTC_OSC_32KCLK_EN);
	}

	/* clear old status */
	reg = rtc_read(rtc, OMAP_RTC_STATUS_REG);

	mask = OMAP_RTC_STATUS_ALARM;

	if (rtc->type->has_pmic_mode)
		mask |= OMAP_RTC_STATUS_ALARM2;

	if (rtc->type->has_power_up_reset) {
		mask |= OMAP_RTC_STATUS_POWER_UP;
		if (reg & OMAP_RTC_STATUS_POWER_UP)
			dev_info(&pdev->dev, "RTC power up reset detected\n");
	}

	if (reg & mask)
		rtc_write(rtc, OMAP_RTC_STATUS_REG, reg & mask);

	/* On boards with split power, RTC_ON_NOFF won't reset the RTC */
	reg = rtc_read(rtc, OMAP_RTC_CTRL_REG);
	if (reg & OMAP_RTC_CTRL_STOP)
		dev_info(&pdev->dev, "already running\n");

	/* force to 24 hour mode */
	new_ctrl = reg & (OMAP_RTC_CTRL_SPLIT | OMAP_RTC_CTRL_AUTO_COMP);
	new_ctrl |= OMAP_RTC_CTRL_STOP;

	/*
	 * BOARD-SPECIFIC CUSTOMIZATION CAN GO HERE:
	 *
	 *  - Device wake-up capability setting should come through chip
	 *    init logic. OMAP1 boards should initialize the "wakeup capable"
	 *    flag in the platform device if the board is wired right for
	 *    being woken up by RTC alarm. For OMAP-L138, this capability
	 *    is built into the SoC by the "Deep Sleep" capability.
	 *
	 *  - Boards wired so RTC_ON_nOFF is used as the reset signal,
	 *    rather than nPWRON_RESET, should forcibly enable split
	 *    power mode.  (Some chip errata report that RTC_CTRL_SPLIT
	 *    is write-only, and always reads as zero...)
	 */

	if (new_ctrl & OMAP_RTC_CTRL_SPLIT)
		dev_info(&pdev->dev, "split power mode\n");

	if (reg != new_ctrl)
		rtc_write(rtc, OMAP_RTC_CTRL_REG, new_ctrl);

	/*
	 * If we have the external clock then switch to it so we can keep
	 * ticking across suspend.
	 */
	if (rtc->has_ext_clk) {
		reg = rtc_read(rtc, OMAP_RTC_OSC_REG);
		reg &= ~OMAP_RTC_OSC_OSC32K_GZ_DISABLE;
		reg |= OMAP_RTC_OSC_32KCLK_EN | OMAP_RTC_OSC_SEL_32KCLK_SRC;
		rtc_writel(rtc, OMAP_RTC_OSC_REG, reg);
	}

	rtc->type->lock(rtc);

	device_init_wakeup(&pdev->dev, true);

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc)) {
		ret = PTR_ERR(rtc->rtc);
		goto err;
	}

	rtc->rtc->ops = &omap_rtc_ops;
	rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->rtc->range_max = RTC_TIMESTAMP_END_2099;
	omap_rtc_nvmem_config.priv = rtc;

	/* handle periodic and alarm irqs */
	ret = devm_request_irq(&pdev->dev, rtc->irq_timer, rtc_irq, 0,
			dev_name(&rtc->rtc->dev), rtc);
	if (ret)
		goto err;

	if (rtc->irq_timer != rtc->irq_alarm) {
		ret = devm_request_irq(&pdev->dev, rtc->irq_alarm, rtc_irq, 0,
				dev_name(&rtc->rtc->dev), rtc);
		if (ret)
			goto err;
	}

	/* Support ext_wakeup pinconf */
	rtc_pinctrl_desc.name = dev_name(&pdev->dev);

	rtc->pctldev = pinctrl_register(&rtc_pinctrl_desc, &pdev->dev, rtc);
	if (IS_ERR(rtc->pctldev)) {
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		ret = PTR_ERR(rtc->pctldev);
		goto err;
	}

	ret = rtc_register_device(rtc->rtc);
	if (ret)
		goto err_deregister_pinctrl;

	rtc_nvmem_register(rtc->rtc, &omap_rtc_nvmem_config);

	if (rtc->is_pmic_controller) {
		if (!pm_power_off) {
			omap_rtc_power_off_rtc = rtc;
			pm_power_off = omap_rtc_power_off;
		}
	}

	return 0;

err_deregister_pinctrl:
	pinctrl_unregister(rtc->pctldev);
err:
	clk_disable_unprepare(rtc->clk);
	device_init_wakeup(&pdev->dev, false);
	rtc->type->lock(rtc);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return ret;
}