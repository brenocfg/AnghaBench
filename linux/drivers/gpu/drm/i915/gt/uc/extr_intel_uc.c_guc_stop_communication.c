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
struct intel_guc {int /*<<< orphan*/  handler; int /*<<< orphan*/  send; int /*<<< orphan*/  ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_clear_mmio_msg (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_ct_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_send_nop ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler_nop ; 

__attribute__((used)) static void guc_stop_communication(struct intel_guc *guc)
{
	intel_guc_ct_stop(&guc->ct);

	guc->send = intel_guc_send_nop;
	guc->handler = intel_guc_to_host_event_handler_nop;

	guc_clear_mmio_msg(guc);
}