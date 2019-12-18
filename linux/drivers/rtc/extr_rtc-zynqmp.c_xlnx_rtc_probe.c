#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct xlnx_rtc_dev {scalar_t__ alarm_irq; scalar_t__ sec_irq; TYPE_1__* rtc; int /*<<< orphan*/  calibval; TYPE_1__* reg_base; } ;
struct resource {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RTC_CALIB_DEF ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 TYPE_1__* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct xlnx_rtc_dev* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xlnx_rtc_dev*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_3__*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xlnx_rtc_dev*) ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  xlnx_init_rtc (struct xlnx_rtc_dev*) ; 
 int /*<<< orphan*/  xlnx_rtc_interrupt ; 
 int /*<<< orphan*/  xlnx_rtc_ops ; 

__attribute__((used)) static int xlnx_rtc_probe(struct platform_device *pdev)
{
	struct xlnx_rtc_dev *xrtcdev;
	struct resource *res;
	int ret;

	xrtcdev = devm_kzalloc(&pdev->dev, sizeof(*xrtcdev), GFP_KERNEL);
	if (!xrtcdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, xrtcdev);

	xrtcdev->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(xrtcdev->rtc))
		return PTR_ERR(xrtcdev->rtc);

	xrtcdev->rtc->ops = &xlnx_rtc_ops;
	xrtcdev->rtc->range_max = U32_MAX;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	xrtcdev->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xrtcdev->reg_base))
		return PTR_ERR(xrtcdev->reg_base);

	xrtcdev->alarm_irq = platform_get_irq_byname(pdev, "alarm");
	if (xrtcdev->alarm_irq < 0)
		return xrtcdev->alarm_irq;
	ret = devm_request_irq(&pdev->dev, xrtcdev->alarm_irq,
			       xlnx_rtc_interrupt, 0,
			       dev_name(&pdev->dev), xrtcdev);
	if (ret) {
		dev_err(&pdev->dev, "request irq failed\n");
		return ret;
	}

	xrtcdev->sec_irq = platform_get_irq_byname(pdev, "sec");
	if (xrtcdev->sec_irq < 0)
		return xrtcdev->sec_irq;
	ret = devm_request_irq(&pdev->dev, xrtcdev->sec_irq,
			       xlnx_rtc_interrupt, 0,
			       dev_name(&pdev->dev), xrtcdev);
	if (ret) {
		dev_err(&pdev->dev, "request irq failed\n");
		return ret;
	}

	ret = of_property_read_u32(pdev->dev.of_node, "calibration",
				   &xrtcdev->calibval);
	if (ret)
		xrtcdev->calibval = RTC_CALIB_DEF;

	xlnx_init_rtc(xrtcdev);

	device_init_wakeup(&pdev->dev, 1);

	return rtc_register_device(xrtcdev->rtc);
}