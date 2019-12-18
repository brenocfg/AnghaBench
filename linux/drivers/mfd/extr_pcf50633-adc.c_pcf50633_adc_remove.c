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
struct platform_device {int dummy; } ;
struct pcf50633_adc {int queue_head; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/ * queue; TYPE_1__* pcf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF50633_IRQ_ADCRDY ; 
 int PCF50633_MAX_ADC_FIFO_DEPTH ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf50633_free_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct pcf50633_adc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pcf50633_adc_remove(struct platform_device *pdev)
{
	struct pcf50633_adc *adc = platform_get_drvdata(pdev);
	int i, head;

	pcf50633_free_irq(adc->pcf, PCF50633_IRQ_ADCRDY);

	mutex_lock(&adc->queue_mutex);
	head = adc->queue_head;

	if (WARN_ON(adc->queue[head]))
		dev_err(adc->pcf->dev,
			"adc driver removed with request pending\n");

	for (i = 0; i < PCF50633_MAX_ADC_FIFO_DEPTH; i++)
		kfree(adc->queue[i]);

	mutex_unlock(&adc->queue_mutex);

	return 0;
}