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
struct pvscsi_adapter {scalar_t__ workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  ll_adapter_reset (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_mask_intr (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_completion_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_process_request_ring (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_shutdown_intr (struct pvscsi_adapter*) ; 

__attribute__((used)) static void __pvscsi_shutdown(struct pvscsi_adapter *adapter)
{
	pvscsi_mask_intr(adapter);

	if (adapter->workqueue)
		flush_workqueue(adapter->workqueue);

	pvscsi_shutdown_intr(adapter);

	pvscsi_process_request_ring(adapter);
	pvscsi_process_completion_ring(adapter);
	ll_adapter_reset(adapter);
}