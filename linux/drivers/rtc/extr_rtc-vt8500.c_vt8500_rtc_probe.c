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
struct vt8500_rtc {int irq_alarm; scalar_t__ rtc; scalar_t__ regbase; int /*<<< orphan*/  lock; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ VT8500_RTC_CR ; 
 int /*<<< orphan*/  VT8500_RTC_CR_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct vt8500_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vt8500_rtc*) ; 
 scalar_t__ devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vt8500_rtc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt8500_rtc_irq ; 
 int /*<<< orphan*/  vt8500_rtc_ops ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int vt8500_rtc_probe(struct platform_device *pdev)
{
	struct vt8500_rtc *vt8500_rtc;
	struct resource	*res;
	int ret;

	vt8500_rtc = devm_kzalloc(&pdev->dev,
			   sizeof(struct vt8500_rtc), GFP_KERNEL);
	if (!vt8500_rtc)
		return -ENOMEM;

	spin_lock_init(&vt8500_rtc->lock);
	platform_set_drvdata(pdev, vt8500_rtc);

	vt8500_rtc->irq_alarm = platform_get_irq(pdev, 0);
	if (vt8500_rtc->irq_alarm < 0)
		return vt8500_rtc->irq_alarm;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vt8500_rtc->regbase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(vt8500_rtc->regbase))
		return PTR_ERR(vt8500_rtc->regbase);

	/* Enable RTC and set it to 24-hour mode */
	writel(VT8500_RTC_CR_ENABLE,
	       vt8500_rtc->regbase + VT8500_RTC_CR);

	vt8500_rtc->rtc = devm_rtc_device_register(&pdev->dev, "vt8500-rtc",
					      &vt8500_rtc_ops, THIS_MODULE);
	if (IS_ERR(vt8500_rtc->rtc)) {
		ret = PTR_ERR(vt8500_rtc->rtc);
		dev_err(&pdev->dev,
			"Failed to register RTC device -> %d\n", ret);
		goto err_return;
	}

	ret = devm_request_irq(&pdev->dev, vt8500_rtc->irq_alarm,
				vt8500_rtc_irq, 0, "rtc alarm", vt8500_rtc);
	if (ret < 0) {
		dev_err(&pdev->dev, "can't get irq %i, err %d\n",
			vt8500_rtc->irq_alarm, ret);
		goto err_return;
	}

	return 0;

err_return:
	return ret;
}