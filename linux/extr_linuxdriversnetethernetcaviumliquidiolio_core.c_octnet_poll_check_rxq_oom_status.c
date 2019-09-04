#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct octeon_droq {int dummy; } ;
struct octeon_device {struct octeon_droq** droq; } ;
struct TYPE_9__ {int /*<<< orphan*/  work; } ;
struct TYPE_10__ {TYPE_4__ wk; int /*<<< orphan*/  wq; } ;
struct TYPE_8__ {int num_rxpciq; TYPE_2__* rxpciq; } ;
struct lio {TYPE_5__ rxq_status_wq; TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct cavium_wk {scalar_t__ ctxptr; } ;
struct TYPE_6__ {int q_no; } ;
struct TYPE_7__ {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_IFSTATE_RUNNING ; 
 int /*<<< orphan*/  LIO_OOM_POLL_INTERVAL_MS ; 
 scalar_t__ ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_droq_check_oom (struct octeon_droq*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octnet_poll_check_rxq_oom_status(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct lio *lio = (struct lio *)wk->ctxptr;
	struct octeon_device *oct = lio->oct_dev;
	struct octeon_droq *droq;
	int q, q_no = 0;

	if (ifstate_check(lio, LIO_IFSTATE_RUNNING)) {
		for (q = 0; q < lio->linfo.num_rxpciq; q++) {
			q_no = lio->linfo.rxpciq[q].s.q_no;
			droq = oct->droq[q_no];
			if (!droq)
				continue;
			octeon_droq_check_oom(droq);
		}
	}
	queue_delayed_work(lio->rxq_status_wq.wq,
			   &lio->rxq_status_wq.wk.work,
			   msecs_to_jiffies(LIO_OOM_POLL_INTERVAL_MS));
}