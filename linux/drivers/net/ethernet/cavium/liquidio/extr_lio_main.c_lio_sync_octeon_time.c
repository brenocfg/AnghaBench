#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct work_struct {int dummy; } ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct octeon_soft_command {int /*<<< orphan*/  caller_is_done; int /*<<< orphan*/  sc_status; int /*<<< orphan*/  complete; int /*<<< orphan*/  iq_no; scalar_t__ virtdptr; } ;
struct octeon_device {TYPE_4__* pci_dev; } ;
struct lio_time {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct TYPE_11__ {int /*<<< orphan*/  work; } ;
struct TYPE_12__ {TYPE_5__ wk; int /*<<< orphan*/  wq; } ;
struct TYPE_9__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_6__ sync_octeon_time_wq; TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct cavium_wk {scalar_t__ ctxptr; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_8__ {TYPE_1__ s; } ;

/* Variables and functions */
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  LIO_SYNC_OCTEON_TIME_INTERVAL_MS ; 
 int /*<<< orphan*/  OCTEON_REQUEST_PENDING ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_SYNC_OCTEON_TIME ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct octeon_soft_command* octeon_alloc_soft_command (struct octeon_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lio_sync_octeon_time(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct lio *lio = (struct lio *)wk->ctxptr;
	struct octeon_device *oct = lio->oct_dev;
	struct octeon_soft_command *sc;
	struct timespec64 ts;
	struct lio_time *lt;
	int ret;

	sc = octeon_alloc_soft_command(oct, sizeof(struct lio_time), 16, 0);
	if (!sc) {
		dev_err(&oct->pci_dev->dev,
			"Failed to sync time to octeon: soft command allocation failed\n");
		return;
	}

	lt = (struct lio_time *)sc->virtdptr;

	/* Get time of the day */
	ktime_get_real_ts64(&ts);
	lt->sec = ts.tv_sec;
	lt->nsec = ts.tv_nsec;
	octeon_swap_8B_data((u64 *)lt, (sizeof(struct lio_time)) / 8);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_SYNC_OCTEON_TIME, 0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ret = octeon_send_soft_command(oct, sc);
	if (ret == IQ_SEND_FAILED) {
		dev_err(&oct->pci_dev->dev,
			"Failed to sync time to octeon: failed to send soft command\n");
		octeon_free_soft_command(oct, sc);
	} else {
		WRITE_ONCE(sc->caller_is_done, true);
	}

	queue_delayed_work(lio->sync_octeon_time_wq.wq,
			   &lio->sync_octeon_time_wq.wk.work,
			   msecs_to_jiffies(LIO_SYNC_OCTEON_TIME_INTERVAL_MS));
}