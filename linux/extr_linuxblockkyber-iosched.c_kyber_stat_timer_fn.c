#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kyber_queue_data {int /*<<< orphan*/  cb; TYPE_3__* domain_tokens; int /*<<< orphan*/  write_lat_nsec; int /*<<< orphan*/  read_lat_nsec; } ;
struct blk_stat_callback {TYPE_1__* stat; struct kyber_queue_data* data; } ;
struct TYPE_5__ {scalar_t__ depth; } ;
struct TYPE_6__ {TYPE_2__ sb; } ;
struct TYPE_4__ {scalar_t__ nr_samples; } ;

/* Variables and functions */
 scalar_t__ IS_BAD (int) ; 
 size_t KYBER_OTHER ; 
 int /*<<< orphan*/  KYBER_READ ; 
 int /*<<< orphan*/  KYBER_SYNC_WRITE ; 
 int /*<<< orphan*/  blk_stat_activate_msecs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_stat_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kyber_adjust_other_depth (struct kyber_queue_data*,int,int,int) ; 
 int /*<<< orphan*/  kyber_adjust_rw_depth (struct kyber_queue_data*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__* kyber_depth ; 
 int kyber_lat_status (struct blk_stat_callback*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kyber_stat_timer_fn(struct blk_stat_callback *cb)
{
	struct kyber_queue_data *kqd = cb->data;
	int read_status, write_status;

	read_status = kyber_lat_status(cb, KYBER_READ, kqd->read_lat_nsec);
	write_status = kyber_lat_status(cb, KYBER_SYNC_WRITE, kqd->write_lat_nsec);

	kyber_adjust_rw_depth(kqd, KYBER_READ, read_status, write_status);
	kyber_adjust_rw_depth(kqd, KYBER_SYNC_WRITE, write_status, read_status);
	kyber_adjust_other_depth(kqd, read_status, write_status,
				 cb->stat[KYBER_OTHER].nr_samples != 0);

	/*
	 * Continue monitoring latencies if we aren't hitting the targets or
	 * we're still throttling other requests.
	 */
	if (!blk_stat_is_active(kqd->cb) &&
	    ((IS_BAD(read_status) || IS_BAD(write_status) ||
	      kqd->domain_tokens[KYBER_OTHER].sb.depth < kyber_depth[KYBER_OTHER])))
		blk_stat_activate_msecs(kqd->cb, 100);
}