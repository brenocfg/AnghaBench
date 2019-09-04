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
typedef  int u64 ;
struct ehea_eqe {scalar_t__ entry; } ;
struct ehea_adapter {TYPE_1__* neq; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_handle; } ;

/* Variables and functions */
 int EHEA_BMASK_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NELR_ADAPTER_MALFUNC ; 
 int /*<<< orphan*/  NELR_PORTSTATE_CHG ; 
 int /*<<< orphan*/  NELR_PORT_MALFUNC ; 
 int /*<<< orphan*/  ehea_h_reset_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ehea_parse_eqe (struct ehea_adapter*,scalar_t__) ; 
 struct ehea_eqe* ehea_poll_eq (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void ehea_neq_tasklet(unsigned long data)
{
	struct ehea_adapter *adapter = (struct ehea_adapter *)data;
	struct ehea_eqe *eqe;
	u64 event_mask;

	eqe = ehea_poll_eq(adapter->neq);
	pr_debug("eqe=%p\n", eqe);

	while (eqe) {
		pr_debug("*eqe=%lx\n", (unsigned long) eqe->entry);
		ehea_parse_eqe(adapter, eqe->entry);
		eqe = ehea_poll_eq(adapter->neq);
		pr_debug("next eqe=%p\n", eqe);
	}

	event_mask = EHEA_BMASK_SET(NELR_PORTSTATE_CHG, 1)
		   | EHEA_BMASK_SET(NELR_ADAPTER_MALFUNC, 1)
		   | EHEA_BMASK_SET(NELR_PORT_MALFUNC, 1);

	ehea_h_reset_events(adapter->handle,
			    adapter->neq->fw_handle, event_mask);
}