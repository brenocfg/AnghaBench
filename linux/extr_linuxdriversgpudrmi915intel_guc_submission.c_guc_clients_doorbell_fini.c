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
struct intel_guc {scalar_t__ execbuf_client; scalar_t__ preempt_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_DOORBELL_INVALID ; 
 int /*<<< orphan*/  __destroy_doorbell (scalar_t__) ; 
 int /*<<< orphan*/  __update_doorbell_desc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guc_clients_doorbell_fini(struct intel_guc *guc)
{
	/*
	 * By the time we're here, GuC has already been reset.
	 * Instead of trying (in vain) to communicate with it, let's just
	 * cleanup the doorbell HW and our internal state.
	 */
	if (guc->preempt_client) {
		__destroy_doorbell(guc->preempt_client);
		__update_doorbell_desc(guc->preempt_client,
				       GUC_DOORBELL_INVALID);
	}

	if (guc->execbuf_client) {
		__destroy_doorbell(guc->execbuf_client);
		__update_doorbell_desc(guc->execbuf_client,
				       GUC_DOORBELL_INVALID);
	}
}