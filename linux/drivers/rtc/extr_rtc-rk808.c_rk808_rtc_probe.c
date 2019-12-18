#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct rk808_rtc {int irq; TYPE_1__* rtc; TYPE_2__* creg; struct rk808* rk808; } ;
struct rk808 {int variant; int /*<<< orphan*/  regmap; } ;
struct TYPE_14__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  status_reg; int /*<<< orphan*/  ctrl_reg; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int BIT_RTC_CTRL_REG_RTC_READSEL_M ; 
 int BIT_RTC_CTRL_REG_STOP_RTC_M ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
#define  RK809_ID 129 
#define  RK817_ID 128 
 int /*<<< orphan*/  RTC_STATUS_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,int,...) ; 
 struct rk808* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_5__*,int) ; 
 struct rk808_rtc* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rk808_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_5__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rk808_rtc*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk808_alarm_irq ; 
 TYPE_2__ rk808_creg ; 
 int /*<<< orphan*/  rk808_rtc_ops ; 
 TYPE_2__ rk817_creg ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int rk808_rtc_probe(struct platform_device *pdev)
{
	struct rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	struct rk808_rtc *rk808_rtc;
	int ret;

	rk808_rtc = devm_kzalloc(&pdev->dev, sizeof(*rk808_rtc), GFP_KERNEL);
	if (rk808_rtc == NULL)
		return -ENOMEM;

	switch (rk808->variant) {
	case RK809_ID:
	case RK817_ID:
		rk808_rtc->creg = &rk817_creg;
		break;
	default:
		rk808_rtc->creg = &rk808_creg;
		break;
	}
	platform_set_drvdata(pdev, rk808_rtc);
	rk808_rtc->rk808 = rk808;

	/* start rtc running by default, and use shadowed timer. */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_STOP_RTC_M |
				 BIT_RTC_CTRL_REG_RTC_READSEL_M,
				 BIT_RTC_CTRL_REG_RTC_READSEL_M);
	if (ret) {
		dev_err(&pdev->dev,
			"Failed to update RTC control: %d\n", ret);
		return ret;
	}

	ret = regmap_write(rk808->regmap, rk808_rtc->creg->status_reg,
			   RTC_STATUS_MASK);
	if (ret) {
		dev_err(&pdev->dev,
			"Failed to write RTC status: %d\n", ret);
		return ret;
	}

	device_init_wakeup(&pdev->dev, 1);

	rk808_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rk808_rtc->rtc))
		return PTR_ERR(rk808_rtc->rtc);

	rk808_rtc->rtc->ops = &rk808_rtc_ops;

	rk808_rtc->irq = platform_get_irq(pdev, 0);
	if (rk808_rtc->irq < 0)
		return rk808_rtc->irq;

	/* request alarm irq of rk808 */
	ret = devm_request_threaded_irq(&pdev->dev, rk808_rtc->irq, NULL,
					rk808_alarm_irq, 0,
					"RTC alarm", rk808_rtc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request alarm IRQ %d: %d\n",
			rk808_rtc->irq, ret);
		return ret;
	}

	return rtc_register_device(rk808_rtc->rtc);
}