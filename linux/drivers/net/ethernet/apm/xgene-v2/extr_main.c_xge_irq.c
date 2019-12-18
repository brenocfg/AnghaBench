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
struct xge_pdata {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xge_intr_disable (struct xge_pdata*) ; 

__attribute__((used)) static irqreturn_t xge_irq(const int irq, void *data)
{
	struct xge_pdata *pdata = data;

	if (napi_schedule_prep(&pdata->napi)) {
		xge_intr_disable(pdata);
		__napi_schedule(&pdata->napi);
	}

	return IRQ_HANDLED;
}