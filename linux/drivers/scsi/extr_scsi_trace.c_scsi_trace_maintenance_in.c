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
typedef  int /*<<< orphan*/  u32 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
#define  MI_MANAGEMENT_PROTOCOL_IN 135 
#define  MI_REPORT_ALIASES 134 
#define  MI_REPORT_IDENTIFYING_INFORMATION 133 
#define  MI_REPORT_PRIORITY 132 
#define  MI_REPORT_SUPPORTED_OPERATION_CODES 131 
#define  MI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS 130 
#define  MI_REPORT_TARGET_PGS 129 
#define  MI_REPORT_TIMESTAMP 128 
 int SERVICE_ACTION16 (unsigned char*) ; 
 int /*<<< orphan*/  get_unaligned_be32 (unsigned char*) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static const char *
scsi_trace_maintenance_in(struct trace_seq *p, unsigned char *cdb, int len)
{
	const char *ret = trace_seq_buffer_ptr(p), *cmd;
	u32 alloc_len;

	switch (SERVICE_ACTION16(cdb)) {
	case MI_REPORT_IDENTIFYING_INFORMATION:
		cmd = "REPORT_IDENTIFYING_INFORMATION";
		break;
	case MI_REPORT_TARGET_PGS:
		cmd = "REPORT_TARGET_PORT_GROUPS";
		break;
	case MI_REPORT_ALIASES:
		cmd = "REPORT_ALIASES";
		break;
	case MI_REPORT_SUPPORTED_OPERATION_CODES:
		cmd = "REPORT_SUPPORTED_OPERATION_CODES";
		break;
	case MI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS:
		cmd = "REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS";
		break;
	case MI_REPORT_PRIORITY:
		cmd = "REPORT_PRIORITY";
		break;
	case MI_REPORT_TIMESTAMP:
		cmd = "REPORT_TIMESTAMP";
		break;
	case MI_MANAGEMENT_PROTOCOL_IN:
		cmd = "MANAGEMENT_PROTOCOL_IN";
		break;
	default:
		trace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	alloc_len = get_unaligned_be32(&cdb[6]);

	trace_seq_printf(p, "%s alloc_len=%u", cmd, alloc_len);

out:
	trace_seq_putc(p, 0);

	return ret;
}