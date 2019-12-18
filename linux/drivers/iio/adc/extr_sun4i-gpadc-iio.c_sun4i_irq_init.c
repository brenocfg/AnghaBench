#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sun4i_gpadc_iio {int dummy; } ;
struct sun4i_gpadc_dev {int /*<<< orphan*/  regmap_irqc; } ;
struct TYPE_4__ {struct TYPE_4__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char const*,...) ; 
 struct sun4i_gpadc_dev* dev_get_drvdata (TYPE_1__*) ; 
 int devm_request_any_context_irq (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct sun4i_gpadc_iio*) ; 
 int /*<<< orphan*/  disable_irq (unsigned int) ; 
 struct sun4i_gpadc_iio* iio_priv (struct sun4i_gpadc_dev*) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_irq_init(struct platform_device *pdev, const char *name,
			  irq_handler_t handler, const char *devname,
			  unsigned int *irq, atomic_t *atomic)
{
	int ret;
	struct sun4i_gpadc_dev *mfd_dev = dev_get_drvdata(pdev->dev.parent);
	struct sun4i_gpadc_iio *info = iio_priv(dev_get_drvdata(&pdev->dev));

	/*
	 * Once the interrupt is activated, the IP continuously performs
	 * conversions thus throws interrupts. The interrupt is activated right
	 * after being requested but we want to control when these interrupts
	 * occur thus we disable it right after being requested. However, an
	 * interrupt might occur between these two instructions and we have to
	 * make sure that does not happen, by using atomic flags. We set the
	 * flag before requesting the interrupt and unset it right after
	 * disabling the interrupt. When an interrupt occurs between these two
	 * instructions, reading the atomic flag will tell us to ignore the
	 * interrupt.
	 */
	atomic_set(atomic, 1);

	ret = platform_get_irq_byname(pdev, name);
	if (ret < 0)
		return ret;

	ret = regmap_irq_get_virq(mfd_dev->regmap_irqc, ret);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get virq for irq %s\n", name);
		return ret;
	}

	*irq = ret;
	ret = devm_request_any_context_irq(&pdev->dev, *irq, handler, 0,
					   devname, info);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not request %s interrupt: %d\n",
			name, ret);
		return ret;
	}

	disable_irq(*irq);
	atomic_set(atomic, 0);

	return 0;
}