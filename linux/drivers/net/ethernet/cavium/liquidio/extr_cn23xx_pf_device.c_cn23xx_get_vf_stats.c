#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int resp_needed; int len; int /*<<< orphan*/  cmd; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ s; scalar_t__ u64; } ;
struct octeon_mbox_cmd {int q_no; int /*<<< orphan*/  data; void* fn_arg; scalar_t__ fn; scalar_t__ recv_status; scalar_t__ recv_len; TYPE_2__ msg; } ;
struct TYPE_7__ {unsigned long long vf_drv_loaded_mask; int rings_per_vf; } ;
struct octeon_device {TYPE_4__* pci_dev; TYPE_3__ sriov_info; } ;
struct oct_vf_stats_ctx {int /*<<< orphan*/  status; struct oct_vf_stats* stats; } ;
struct oct_vf_stats {int dummy; } ;
typedef  scalar_t__ octeon_mbox_callback_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  OCTEON_GET_VF_STATS ; 
 int /*<<< orphan*/  OCTEON_MBOX_REQUEST ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cn23xx_get_vf_stats_callback ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octeon_mbox_cancel (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_mbox_write (struct octeon_device*,struct octeon_mbox_cmd*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

int cn23xx_get_vf_stats(struct octeon_device *oct, int vfidx,
			struct oct_vf_stats *stats)
{
	u32 timeout = HZ; // 1sec
	struct octeon_mbox_cmd mbox_cmd;
	struct oct_vf_stats_ctx ctx;
	u32 count = 0, ret;

	if (!(oct->sriov_info.vf_drv_loaded_mask & (1ULL << vfidx)))
		return -1;

	if (sizeof(struct oct_vf_stats) > sizeof(mbox_cmd.data))
		return -1;

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
	mbox_cmd.msg.s.resp_needed = 1;
	mbox_cmd.msg.s.cmd = OCTEON_GET_VF_STATS;
	mbox_cmd.msg.s.len = 1;
	mbox_cmd.q_no = vfidx * oct->sriov_info.rings_per_vf;
	mbox_cmd.recv_len = 0;
	mbox_cmd.recv_status = 0;
	mbox_cmd.fn = (octeon_mbox_callback_t)cn23xx_get_vf_stats_callback;
	ctx.stats = stats;
	atomic_set(&ctx.status, 0);
	mbox_cmd.fn_arg = (void *)&ctx;
	memset(mbox_cmd.data, 0, sizeof(mbox_cmd.data));
	octeon_mbox_write(oct, &mbox_cmd);

	do {
		schedule_timeout_uninterruptible(1);
	} while ((atomic_read(&ctx.status) == 0) && (count++ < timeout));

	ret = atomic_read(&ctx.status);
	if (ret == 0) {
		octeon_mbox_cancel(oct, 0);
		dev_err(&oct->pci_dev->dev, "Unable to get stats from VF-%d, timedout\n",
			vfidx);
		return -1;
	}

	return 0;
}