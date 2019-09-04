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
typedef  scalar_t__ u64 ;
struct request {int rq_flags; int /*<<< orphan*/  q; scalar_t__ start_time_ns; struct hd_struct* part; } ;
struct hd_struct {int dummy; } ;

/* Variables and functions */
 int RQF_FLUSH_SEQ ; 
 scalar_t__ blk_do_io_stat (struct request*) ; 
 int /*<<< orphan*/  hd_struct_put (struct hd_struct*) ; 
 int /*<<< orphan*/ * ios ; 
 int /*<<< orphan*/ * nsecs ; 
 int op_stat_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_dec_in_flight (int /*<<< orphan*/ ,struct hd_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_round_stats (int /*<<< orphan*/ ,int,struct hd_struct*) ; 
 int /*<<< orphan*/  part_stat_add (int,struct hd_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  part_stat_inc (int,struct hd_struct*,int /*<<< orphan*/ ) ; 
 int part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int /*<<< orphan*/  req_op (struct request*) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 

void blk_account_io_done(struct request *req, u64 now)
{
	/*
	 * Account IO completion.  flush_rq isn't accounted as a
	 * normal IO on queueing nor completion.  Accounting the
	 * containing request is enough.
	 */
	if (blk_do_io_stat(req) && !(req->rq_flags & RQF_FLUSH_SEQ)) {
		const int sgrp = op_stat_group(req_op(req));
		struct hd_struct *part;
		int cpu;

		cpu = part_stat_lock();
		part = req->part;

		part_stat_inc(cpu, part, ios[sgrp]);
		part_stat_add(cpu, part, nsecs[sgrp], now - req->start_time_ns);
		part_round_stats(req->q, cpu, part);
		part_dec_in_flight(req->q, part, rq_data_dir(req));

		hd_struct_put(part);
		part_stat_unlock();
	}
}