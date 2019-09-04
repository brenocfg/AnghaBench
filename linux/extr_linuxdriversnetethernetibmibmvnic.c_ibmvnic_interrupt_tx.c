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
struct ibmvnic_sub_crq_queue {struct ibmvnic_adapter* adapter; } ;
struct ibmvnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_scrq_irq (struct ibmvnic_adapter*,struct ibmvnic_sub_crq_queue*) ; 
 int /*<<< orphan*/  ibmvnic_complete_tx (struct ibmvnic_adapter*,struct ibmvnic_sub_crq_queue*) ; 

__attribute__((used)) static irqreturn_t ibmvnic_interrupt_tx(int irq, void *instance)
{
	struct ibmvnic_sub_crq_queue *scrq = instance;
	struct ibmvnic_adapter *adapter = scrq->adapter;

	disable_scrq_irq(adapter, scrq);
	ibmvnic_complete_tx(adapter, scrq);

	return IRQ_HANDLED;
}