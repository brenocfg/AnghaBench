#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct cec_gpio {TYPE_1__* adap; void* v5_irq; TYPE_1__* v5_gpio; void* hpd_irq; TYPE_1__* hpd_gpio; void* cec_irq; TYPE_1__* cec_gpio; struct device* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CEC_CAP_DEFAULTS ; 
 int CEC_CAP_MONITOR_ALL ; 
 int CEC_CAP_MONITOR_PIN ; 
 int CEC_CAP_PHYS_ADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH_OPEN_DRAIN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  cec_5v_gpio_irq_handler ; 
 int /*<<< orphan*/  cec_5v_gpio_irq_handler_thread ; 
 int /*<<< orphan*/  cec_delete_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  cec_gpio_disable_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  cec_gpio_irq_handler ; 
 int /*<<< orphan*/  cec_gpio_pin_ops ; 
 int /*<<< orphan*/  cec_hpd_gpio_irq_handler ; 
 int /*<<< orphan*/  cec_hpd_gpio_irq_handler_thread ; 
 TYPE_1__* cec_pin_allocate_adapter (int /*<<< orphan*/ *,struct cec_gpio*,int /*<<< orphan*/ ,int) ; 
 int cec_register_adapter (TYPE_1__*,struct device*) ; 
 TYPE_1__* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct cec_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cec_gpio*) ; 
 int devm_request_threaded_irq (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct cec_gpio*) ; 
 void* gpiod_to_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cec_gpio*) ; 

__attribute__((used)) static int cec_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct cec_gpio *cec;
	int ret;

	cec = devm_kzalloc(dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
		return -ENOMEM;

	cec->dev = dev;

	cec->cec_gpio = devm_gpiod_get(dev, "cec", GPIOD_OUT_HIGH_OPEN_DRAIN);
	if (IS_ERR(cec->cec_gpio))
		return PTR_ERR(cec->cec_gpio);
	cec->cec_irq = gpiod_to_irq(cec->cec_gpio);

	cec->hpd_gpio = devm_gpiod_get_optional(dev, "hpd", GPIOD_IN);
	if (IS_ERR(cec->hpd_gpio))
		return PTR_ERR(cec->hpd_gpio);

	cec->v5_gpio = devm_gpiod_get_optional(dev, "v5", GPIOD_IN);
	if (IS_ERR(cec->v5_gpio))
		return PTR_ERR(cec->v5_gpio);

	cec->adap = cec_pin_allocate_adapter(&cec_gpio_pin_ops,
		cec, pdev->name, CEC_CAP_DEFAULTS | CEC_CAP_PHYS_ADDR |
				 CEC_CAP_MONITOR_ALL | CEC_CAP_MONITOR_PIN);
	if (IS_ERR(cec->adap))
		return PTR_ERR(cec->adap);

	ret = devm_request_irq(dev, cec->cec_irq, cec_gpio_irq_handler,
			       IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			       cec->adap->name, cec);
	if (ret)
		return ret;

	cec_gpio_disable_irq(cec->adap);

	if (cec->hpd_gpio) {
		cec->hpd_irq = gpiod_to_irq(cec->hpd_gpio);
		ret = devm_request_threaded_irq(dev, cec->hpd_irq,
			cec_hpd_gpio_irq_handler,
			cec_hpd_gpio_irq_handler_thread,
			IRQF_ONESHOT |
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
			"hpd-gpio", cec);
		if (ret)
			return ret;
	}

	if (cec->v5_gpio) {
		cec->v5_irq = gpiod_to_irq(cec->v5_gpio);
		ret = devm_request_threaded_irq(dev, cec->v5_irq,
			cec_5v_gpio_irq_handler,
			cec_5v_gpio_irq_handler_thread,
			IRQF_ONESHOT |
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
			"v5-gpio", cec);
		if (ret)
			return ret;
	}

	ret = cec_register_adapter(cec->adap, &pdev->dev);
	if (ret) {
		cec_delete_adapter(cec->adap);
		return ret;
	}

	platform_set_drvdata(pdev, cec);
	return 0;
}