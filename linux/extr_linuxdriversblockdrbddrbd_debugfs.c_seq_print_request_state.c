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
struct seq_file {int dummy; } ;
struct drbd_request {unsigned int rq_state; scalar_t__ master_bio; } ;

/* Variables and functions */
 unsigned int RQ_COMPLETION_SUSP ; 
 unsigned int RQ_EXP_BARR_ACK ; 
 unsigned int RQ_EXP_RECEIVE_ACK ; 
 unsigned int RQ_EXP_WRITE_ACK ; 
 unsigned int RQ_IN_ACT_LOG ; 
 unsigned int RQ_LOCAL_ABORTED ; 
 unsigned int RQ_LOCAL_COMPLETED ; 
 unsigned int RQ_LOCAL_OK ; 
 unsigned int RQ_LOCAL_PENDING ; 
 unsigned int RQ_NET_DONE ; 
 unsigned int RQ_NET_OK ; 
 unsigned int RQ_NET_PENDING ; 
 unsigned int RQ_NET_QUEUED ; 
 unsigned int RQ_NET_SENT ; 
 unsigned int RQ_NET_SIS ; 
 unsigned int RQ_POSTPONED ; 
 int /*<<< orphan*/  seq_print_rq_state_bit (struct seq_file*,unsigned int,char*,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void seq_print_request_state(struct seq_file *m, struct drbd_request *req)
{
	unsigned int s = req->rq_state;
	char sep = ' ';
	seq_printf(m, "\t0x%08x", s);
	seq_printf(m, "\tmaster: %s", req->master_bio ? "pending" : "completed");

	/* RQ_WRITE ignored, already reported */
	seq_puts(m, "\tlocal:");
	seq_print_rq_state_bit(m, s & RQ_IN_ACT_LOG, &sep, "in-AL");
	seq_print_rq_state_bit(m, s & RQ_POSTPONED, &sep, "postponed");
	seq_print_rq_state_bit(m, s & RQ_COMPLETION_SUSP, &sep, "suspended");
	sep = ' ';
	seq_print_rq_state_bit(m, s & RQ_LOCAL_PENDING, &sep, "pending");
	seq_print_rq_state_bit(m, s & RQ_LOCAL_COMPLETED, &sep, "completed");
	seq_print_rq_state_bit(m, s & RQ_LOCAL_ABORTED, &sep, "aborted");
	seq_print_rq_state_bit(m, s & RQ_LOCAL_OK, &sep, "ok");
	if (sep == ' ')
		seq_puts(m, " -");

	/* for_each_connection ... */
	seq_printf(m, "\tnet:");
	sep = ' ';
	seq_print_rq_state_bit(m, s & RQ_NET_PENDING, &sep, "pending");
	seq_print_rq_state_bit(m, s & RQ_NET_QUEUED, &sep, "queued");
	seq_print_rq_state_bit(m, s & RQ_NET_SENT, &sep, "sent");
	seq_print_rq_state_bit(m, s & RQ_NET_DONE, &sep, "done");
	seq_print_rq_state_bit(m, s & RQ_NET_SIS, &sep, "sis");
	seq_print_rq_state_bit(m, s & RQ_NET_OK, &sep, "ok");
	if (sep == ' ')
		seq_puts(m, " -");

	seq_printf(m, " :");
	sep = ' ';
	seq_print_rq_state_bit(m, s & RQ_EXP_RECEIVE_ACK, &sep, "B");
	seq_print_rq_state_bit(m, s & RQ_EXP_WRITE_ACK, &sep, "C");
	seq_print_rq_state_bit(m, s & RQ_EXP_BARR_ACK, &sep, "barr");
	if (sep == ' ')
		seq_puts(m, " -");
	seq_printf(m, "\n");
}