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
struct hinic_rxq {struct hinic_rq* rq; } ;
struct hinic_rq {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hinic_rxq*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_del_napi (struct hinic_rxq*) ; 

__attribute__((used)) static void rx_free_irq(struct hinic_rxq *rxq)
{
	struct hinic_rq *rq = rxq->rq;

	irq_set_affinity_hint(rq->irq, NULL);
	free_irq(rq->irq, rxq);
	rx_del_napi(rxq);
}