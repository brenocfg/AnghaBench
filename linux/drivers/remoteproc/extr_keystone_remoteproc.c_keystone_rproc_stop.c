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
struct rproc {struct keystone_rproc* priv; } ;
struct keystone_rproc {int /*<<< orphan*/  workqueue; int /*<<< orphan*/  irq_ring; int /*<<< orphan*/  irq_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct keystone_rproc*) ; 
 int /*<<< orphan*/  keystone_rproc_dsp_reset (struct keystone_rproc*) ; 

__attribute__((used)) static int keystone_rproc_stop(struct rproc *rproc)
{
	struct keystone_rproc *ksproc = rproc->priv;

	keystone_rproc_dsp_reset(ksproc);
	free_irq(ksproc->irq_fault, ksproc);
	free_irq(ksproc->irq_ring, ksproc);
	flush_work(&ksproc->workqueue);

	return 0;
}