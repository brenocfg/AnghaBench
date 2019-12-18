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
struct trace_seq {int dummy; } ;
struct nvmet_ctrl {int /*<<< orphan*/  cntlid; } ;

/* Variables and functions */
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *nvmet_trace_ctrl_name(struct trace_seq *p, struct nvmet_ctrl *ctrl)
{
	const char *ret = trace_seq_buffer_ptr(p);

	/*
	 * XXX: We don't know the controller instance before executing the
	 * connect command itself because the connect command for the admin
	 * queue will not provide the cntlid which will be allocated in this
	 * command.  In case of io queues, the controller instance will be
	 * mapped by the extra data of the connect command.
	 * If we can know the extra data of the connect command in this stage,
	 * we can update this print statement later.
	 */
	if (ctrl)
		trace_seq_printf(p, "%d", ctrl->cntlid);
	else
		trace_seq_printf(p, "_");
	trace_seq_putc(p, 0);

	return ret;
}