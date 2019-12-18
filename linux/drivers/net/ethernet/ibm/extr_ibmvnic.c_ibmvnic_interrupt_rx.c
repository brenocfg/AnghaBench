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
struct ibmvnic_sub_crq_queue {size_t scrq_num; struct ibmvnic_adapter* adapter; } ;
struct ibmvnic_adapter {scalar_t__ state; int /*<<< orphan*/ * napi; TYPE_1__* rx_stats_buffers; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ VNIC_OPEN ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_scrq_irq (struct ibmvnic_adapter*,struct ibmvnic_sub_crq_queue*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ibmvnic_interrupt_rx(int irq, void *instance)
{
	struct ibmvnic_sub_crq_queue *scrq = instance;
	struct ibmvnic_adapter *adapter = scrq->adapter;

	/* When booting a kdump kernel we can hit pending interrupts
	 * prior to completing driver initialization.
	 */
	if (unlikely(adapter->state != VNIC_OPEN))
		return IRQ_NONE;

	adapter->rx_stats_buffers[scrq->scrq_num].interrupts++;

	if (napi_schedule_prep(&adapter->napi[scrq->scrq_num])) {
		disable_scrq_irq(adapter, scrq);
		__napi_schedule(&adapter->napi[scrq->scrq_num]);
	}

	return IRQ_HANDLED;
}