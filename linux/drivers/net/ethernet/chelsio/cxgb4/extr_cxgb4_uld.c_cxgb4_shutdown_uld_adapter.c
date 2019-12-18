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
struct adapter {int flags; TYPE_1__* uld; } ;
typedef  enum cxgb4_uld { ____Placeholder_cxgb4_uld } cxgb4_uld ;
struct TYPE_2__ {int /*<<< orphan*/ * add; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int CXGB4_USING_MSIX ; 
 int /*<<< orphan*/  free_msix_queue_irqs_uld (struct adapter*,int) ; 
 int /*<<< orphan*/  free_queues_uld (struct adapter*,int) ; 
 int /*<<< orphan*/  free_sge_queues_uld (struct adapter*,int) ; 
 int /*<<< orphan*/  quiesce_rx_uld (struct adapter*,int) ; 
 int /*<<< orphan*/  release_sge_txq_uld (struct adapter*,int) ; 

__attribute__((used)) static void cxgb4_shutdown_uld_adapter(struct adapter *adap, enum cxgb4_uld type)
{
	if (adap->uld[type].handle) {
		adap->uld[type].handle = NULL;
		adap->uld[type].add = NULL;
		release_sge_txq_uld(adap, type);

		if (adap->flags & CXGB4_FULL_INIT_DONE)
			quiesce_rx_uld(adap, type);

		if (adap->flags & CXGB4_USING_MSIX)
			free_msix_queue_irqs_uld(adap, type);

		free_sge_queues_uld(adap, type);
		free_queues_uld(adap, type);
	}
}