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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int size; scalar_t__ sector; } ;
struct drbd_request {unsigned int rq_state; scalar_t__ net_done_jif; scalar_t__ acked_jif; scalar_t__ pre_send_jif; scalar_t__ pre_submit_jif; scalar_t__ in_actlog_jif; scalar_t__ start_jif; TYPE_1__ i; int /*<<< orphan*/  epoch; } ;

/* Variables and functions */
 unsigned int RQ_IN_ACT_LOG ; 
 unsigned int RQ_LOCAL_PENDING ; 
 unsigned int RQ_NET_DONE ; 
 unsigned int RQ_NET_PENDING ; 
 unsigned int RQ_NET_SENT ; 
 unsigned int RQ_WRITE ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  seq_print_age_or_dash (struct seq_file*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  seq_print_request_state (struct seq_file*,struct drbd_request*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void seq_print_one_request(struct seq_file *m, struct drbd_request *req, unsigned long now)
{
	/* change anything here, fixup header below! */
	unsigned int s = req->rq_state;

#define RQ_HDR_1 "epoch\tsector\tsize\trw"
	seq_printf(m, "0x%x\t%llu\t%u\t%s",
		req->epoch,
		(unsigned long long)req->i.sector, req->i.size >> 9,
		(s & RQ_WRITE) ? "W" : "R");

#define RQ_HDR_2 "\tstart\tin AL\tsubmit"
	seq_printf(m, "\t%d", jiffies_to_msecs(now - req->start_jif));
	seq_print_age_or_dash(m, s & RQ_IN_ACT_LOG, now - req->in_actlog_jif);
	seq_print_age_or_dash(m, s & RQ_LOCAL_PENDING, now - req->pre_submit_jif);

#define RQ_HDR_3 "\tsent\tacked\tdone"
	seq_print_age_or_dash(m, s & RQ_NET_SENT, now - req->pre_send_jif);
	seq_print_age_or_dash(m, (s & RQ_NET_SENT) && !(s & RQ_NET_PENDING), now - req->acked_jif);
	seq_print_age_or_dash(m, s & RQ_NET_DONE, now - req->net_done_jif);

#define RQ_HDR_4 "\tstate\n"
	seq_print_request_state(m, req);
}