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
struct pcf50633_adc_request {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  (* callback ) (struct pcf50633*,int /*<<< orphan*/ ,int) ;} ;
struct pcf50633_adc {int queue_head; int /*<<< orphan*/  queue_mutex; struct pcf50633_adc_request** queue; struct pcf50633* pcf; } ;
struct pcf50633 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCF50633_MAX_ADC_FIFO_DEPTH ; 
 scalar_t__ WARN_ON (int) ; 
 int adc_result (struct pcf50633*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct pcf50633_adc_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pcf50633*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trigger_next_adc_job_if_any (struct pcf50633*) ; 

__attribute__((used)) static void pcf50633_adc_irq(int irq, void *data)
{
	struct pcf50633_adc *adc = data;
	struct pcf50633 *pcf = adc->pcf;
	struct pcf50633_adc_request *req;
	int head, res;

	mutex_lock(&adc->queue_mutex);
	head = adc->queue_head;

	req = adc->queue[head];
	if (WARN_ON(!req)) {
		dev_err(pcf->dev, "pcf50633-adc irq: ADC queue empty!\n");
		mutex_unlock(&adc->queue_mutex);
		return;
	}
	adc->queue[head] = NULL;
	adc->queue_head = (head + 1) &
				      (PCF50633_MAX_ADC_FIFO_DEPTH - 1);

	res = adc_result(pcf);
	trigger_next_adc_job_if_any(pcf);

	mutex_unlock(&adc->queue_mutex);

	req->callback(pcf, req->callback_param, res);
	kfree(req);
}