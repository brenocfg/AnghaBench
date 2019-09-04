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
struct intel_guc_log {int dummy; } ;

/* Variables and functions */
 int INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED ; 
 int INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER ; 
 int /*<<< orphan*/  intel_guc_enable_msg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_to_guc (struct intel_guc_log*) ; 

__attribute__((used)) static void guc_log_enable_flush_events(struct intel_guc_log *log)
{
	intel_guc_enable_msg(log_to_guc(log),
			     INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER |
			     INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED);
}