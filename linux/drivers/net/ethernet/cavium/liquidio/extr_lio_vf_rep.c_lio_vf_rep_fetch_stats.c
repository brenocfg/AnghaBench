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
typedef  int /*<<< orphan*/  u64 ;
struct work_struct {int dummy; } ;
struct octeon_device {int dummy; } ;
struct lio_vf_rep_stats {int dummy; } ;
struct lio_vf_rep_req {int /*<<< orphan*/  ifidx; int /*<<< orphan*/  req_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct lio_vf_rep_desc {TYPE_1__ stats_wk; int /*<<< orphan*/  stats; int /*<<< orphan*/  ifidx; struct octeon_device* oct; } ;
struct cavium_wk {struct lio_vf_rep_desc* ctxptr; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  rep_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_VF_REP_REQ_STATS ; 
 int /*<<< orphan*/  LIO_VF_REP_STATS_POLL_TIME_MS ; 
 int lio_vf_rep_send_soft_command (struct octeon_device*,struct lio_vf_rep_req*,int,struct lio_vf_rep_stats*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct lio_vf_rep_stats*,int) ; 
 int /*<<< orphan*/  memset (struct lio_vf_rep_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_vf_rep_fetch_stats(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct lio_vf_rep_desc *vf_rep = wk->ctxptr;
	struct lio_vf_rep_stats stats;
	struct lio_vf_rep_req rep_cfg;
	struct octeon_device *oct;
	int ret;

	oct = vf_rep->oct;

	memset(&rep_cfg, 0, sizeof(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_STATS;
	rep_cfg.ifidx = vf_rep->ifidx;

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg, sizeof(rep_cfg),
					   &stats, sizeof(stats));

	if (!ret) {
		octeon_swap_8B_data((u64 *)&stats, (sizeof(stats) >> 3));
		memcpy(&vf_rep->stats, &stats, sizeof(stats));
	}

	schedule_delayed_work(&vf_rep->stats_wk.work,
			      msecs_to_jiffies(LIO_VF_REP_STATS_POLL_TIME_MS));
}