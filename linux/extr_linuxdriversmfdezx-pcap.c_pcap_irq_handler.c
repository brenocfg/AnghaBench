#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_chip {int /*<<< orphan*/  isr_work; int /*<<< orphan*/  workqueue; } ;
struct TYPE_4__ {TYPE_1__* chip; } ;
struct irq_desc {TYPE_2__ irq_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_ack ) (TYPE_2__*) ;} ;

/* Variables and functions */
 struct pcap_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void pcap_irq_handler(struct irq_desc *desc)
{
	struct pcap_chip *pcap = irq_desc_get_handler_data(desc);

	desc->irq_data.chip->irq_ack(&desc->irq_data);
	queue_work(pcap->workqueue, &pcap->isr_work);
}