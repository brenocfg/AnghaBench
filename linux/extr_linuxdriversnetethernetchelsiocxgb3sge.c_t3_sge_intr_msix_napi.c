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
struct sge_rspq {int /*<<< orphan*/  lock; int /*<<< orphan*/  unhandled_irqs; } ;
struct sge_qset {int /*<<< orphan*/  adap; struct sge_rspq rspq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ handle_responses (int /*<<< orphan*/ ,struct sge_rspq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t t3_sge_intr_msix_napi(int irq, void *cookie)
{
	struct sge_qset *qs = cookie;
	struct sge_rspq *q = &qs->rspq;

	spin_lock(&q->lock);

	if (handle_responses(qs->adap, q) < 0)
		q->unhandled_irqs++;
	spin_unlock(&q->lock);
	return IRQ_HANDLED;
}