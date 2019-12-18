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
struct fc_lport {int /*<<< orphan*/  stats; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  scsi_pkt_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  timer; int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  xfer_ddp; struct fc_lport* lp; } ;
struct fc_fcp_internal {int /*<<< orphan*/  scsi_pkt_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  FcpPktAllocFails; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct fc_fcp_internal* fc_get_scsi_internal (struct fc_lport*) ; 
 int /*<<< orphan*/  get_cpu () ; 
 struct fc_fcp_pkt* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_fcp_pkt*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fc_fcp_pkt *fc_fcp_pkt_alloc(struct fc_lport *lport, gfp_t gfp)
{
	struct fc_fcp_internal *si = fc_get_scsi_internal(lport);
	struct fc_fcp_pkt *fsp;

	fsp = mempool_alloc(si->scsi_pkt_pool, gfp);
	if (fsp) {
		memset(fsp, 0, sizeof(*fsp));
		fsp->lp = lport;
		fsp->xfer_ddp = FC_XID_UNKNOWN;
		refcount_set(&fsp->ref_cnt, 1);
		timer_setup(&fsp->timer, NULL, 0);
		INIT_LIST_HEAD(&fsp->list);
		spin_lock_init(&fsp->scsi_pkt_lock);
	} else {
		per_cpu_ptr(lport->stats, get_cpu())->FcpPktAllocFails++;
		put_cpu();
	}
	return fsp;
}