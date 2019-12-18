#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcf50633_adc {int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  pcf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCF50633_IRQ_ADCRDY ; 
 int /*<<< orphan*/  dev_to_pcf50633 (int /*<<< orphan*/ ) ; 
 struct pcf50633_adc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf50633_adc_irq ; 
 int /*<<< orphan*/  pcf50633_register_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcf50633_adc*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pcf50633_adc*) ; 

__attribute__((used)) static int pcf50633_adc_probe(struct platform_device *pdev)
{
	struct pcf50633_adc *adc;

	adc = devm_kzalloc(&pdev->dev, sizeof(*adc), GFP_KERNEL);
	if (!adc)
		return -ENOMEM;

	adc->pcf = dev_to_pcf50633(pdev->dev.parent);
	platform_set_drvdata(pdev, adc);

	pcf50633_register_irq(adc->pcf, PCF50633_IRQ_ADCRDY,
					pcf50633_adc_irq, adc);

	mutex_init(&adc->queue_mutex);

	return 0;
}