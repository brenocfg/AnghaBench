#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int tm_year; int tm_mday; scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mon; } ;
struct pm860x_rtc_pdata {int vrtc; int /*<<< orphan*/  (* sync ) (unsigned long) ;} ;
struct pm860x_rtc_info {scalar_t__ irq; int vrtc; int /*<<< orphan*/  calib_work; int /*<<< orphan*/  i2c; int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  (* sync ) (unsigned long) ;TYPE_1__* dev; struct pm860x_chip* chip; } ;
struct pm860x_chip {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  companion; int /*<<< orphan*/  client; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_PM8607 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEAS2_VRTC ; 
 int /*<<< orphan*/  PM8607_MEAS_EN2 ; 
 int /*<<< orphan*/  PM8607_RTC1 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG0_ADDR ; 
 int /*<<< orphan*/  REG0_DATA ; 
 int /*<<< orphan*/  REG1_ADDR ; 
 int /*<<< orphan*/  REG1_DATA ; 
 int /*<<< orphan*/  REG2_ADDR ; 
 int /*<<< orphan*/  REG2_DATA ; 
 int /*<<< orphan*/  REG3_ADDR ; 
 int /*<<< orphan*/  REG3_DATA ; 
 int /*<<< orphan*/  RTC1_USE_XO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VRTC_CALIB_INTERVAL ; 
 int /*<<< orphan*/  calibrate_vrtc_work ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct pm860x_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct pm860x_rtc_pdata* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct pm860x_rtc_info*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct pm860x_rtc_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pm860x_rtc_info*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm860x_page_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pm860x_rtc_dt_init (struct platform_device*,struct pm860x_rtc_info*) ; 
 int /*<<< orphan*/  pm860x_rtc_ops ; 
 int pm860x_rtc_read_time (TYPE_1__*,struct rtc_time*) ; 
 int pm860x_rtc_set_time (TYPE_1__*,struct rtc_time*) ; 
 int /*<<< orphan*/  pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  rtc_update_handler ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 

__attribute__((used)) static int pm860x_rtc_probe(struct platform_device *pdev)
{
	struct pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct pm860x_rtc_pdata *pdata = NULL;
	struct pm860x_rtc_info *info;
	struct rtc_time tm;
	unsigned long ticks = 0;
	int ret;

	pdata = dev_get_platdata(&pdev->dev);

	info = devm_kzalloc(&pdev->dev, sizeof(struct pm860x_rtc_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->irq = platform_get_irq(pdev, 0);
	if (info->irq < 0)
		return info->irq;

	info->chip = chip;
	info->i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, info);

	ret = devm_request_threaded_irq(&pdev->dev, info->irq, NULL,
					rtc_update_handler, IRQF_ONESHOT, "rtc",
					info);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		return ret;
	}

	/* set addresses of 32-bit base value for RTC time */
	pm860x_page_reg_write(info->i2c, REG0_ADDR, REG0_DATA);
	pm860x_page_reg_write(info->i2c, REG1_ADDR, REG1_DATA);
	pm860x_page_reg_write(info->i2c, REG2_ADDR, REG2_DATA);
	pm860x_page_reg_write(info->i2c, REG3_ADDR, REG3_DATA);

	ret = pm860x_rtc_read_time(&pdev->dev, &tm);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to read initial time.\n");
		return ret;
	}
	if ((tm.tm_year < 70) || (tm.tm_year > 138)) {
		tm.tm_year = 70;
		tm.tm_mon = 0;
		tm.tm_mday = 1;
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
		ret = pm860x_rtc_set_time(&pdev->dev, &tm);
		if (ret < 0) {
			dev_err(&pdev->dev, "Failed to set initial time.\n");
			return ret;
		}
	}
	rtc_tm_to_time(&tm, &ticks);
	if (pm860x_rtc_dt_init(pdev, info)) {
		if (pdata && pdata->sync) {
			pdata->sync(ticks);
			info->sync = pdata->sync;
		}
	}

	info->rtc_dev = devm_rtc_device_register(&pdev->dev, "88pm860x-rtc",
					    &pm860x_rtc_ops, THIS_MODULE);
	ret = PTR_ERR(info->rtc_dev);
	if (IS_ERR(info->rtc_dev)) {
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		return ret;
	}

	/*
	 * enable internal XO instead of internal 3.25MHz clock since it can
	 * free running in PMIC power-down state.
	 */
	pm860x_set_bits(info->i2c, PM8607_RTC1, RTC1_USE_XO, RTC1_USE_XO);

#ifdef VRTC_CALIBRATION
	/* <00> -- 2.7V, <01> -- 2.9V, <10> -- 3.1V, <11> -- 3.3V */
	if (pm860x_rtc_dt_init(pdev, info)) {
		if (pdata && pdata->vrtc)
			info->vrtc = pdata->vrtc & 0x3;
		else
			info->vrtc = 1;
	}
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VRTC, MEAS2_VRTC);

	/* calibrate VRTC */
	INIT_DELAYED_WORK(&info->calib_work, calibrate_vrtc_work);
	schedule_delayed_work(&info->calib_work, VRTC_CALIB_INTERVAL);
#endif	/* VRTC_CALIBRATION */

	device_init_wakeup(&pdev->dev, 1);

	return 0;
}