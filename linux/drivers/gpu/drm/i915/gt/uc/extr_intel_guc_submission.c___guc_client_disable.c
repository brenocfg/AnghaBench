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
struct intel_guc_client {int /*<<< orphan*/  guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fini_doorbell (struct intel_guc_client*) ; 
 int /*<<< orphan*/  destroy_doorbell (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_proc_desc_fini (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_stage_desc_fini (struct intel_guc_client*) ; 
 scalar_t__ intel_guc_is_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __guc_client_disable(struct intel_guc_client *client)
{
	/*
	 * By the time we're here, GuC may have already been reset. if that is
	 * the case, instead of trying (in vain) to communicate with it, let's
	 * just cleanup the doorbell HW and our internal state.
	 */
	if (intel_guc_is_running(client->guc))
		destroy_doorbell(client);
	else
		__fini_doorbell(client);

	guc_stage_desc_fini(client);
	guc_proc_desc_fini(client);
}