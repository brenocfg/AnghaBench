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
typedef  int u32 ;
struct intel_guc {int const msg_enabled_mask; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int EPROTO ; 
 int INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED ; 
 int INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER ; 
 int /*<<< orphan*/  intel_guc_log_handle_flush_event (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int intel_guc_to_host_process_recv_msg(struct intel_guc *guc,
				       const u32 *payload, u32 len)
{
	u32 msg;

	if (unlikely(!len))
		return -EPROTO;

	/* Make sure to handle only enabled messages */
	msg = payload[0] & guc->msg_enabled_mask;

	if (msg & (INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER |
		   INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED))
		intel_guc_log_handle_flush_event(&guc->log);

	return 0;
}