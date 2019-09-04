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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {scalar_t__ flags; } ;
struct qib_pportdata {TYPE_2__ cong_stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; void* pma_sample_start; void* pma_sample_interval; int /*<<< orphan*/ * pma_counter_select; int /*<<< orphan*/  pma_tag; } ;
struct qib_ibport {TYPE_3__ rvp; } ;
struct qib_ibdev {int dummy; } ;
struct qib_devdata {scalar_t__ (* f_portcntr ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* f_set_cntr_sample ) (struct qib_pportdata*,void*,void*) ;} ;
struct ib_smp {int dummy; } ;
struct ib_pma_portsamplescontrol {scalar_t__ port_select; int /*<<< orphan*/ * counter_select; int /*<<< orphan*/  tag; int /*<<< orphan*/  sample_interval; int /*<<< orphan*/  sample_start; } ;
struct TYPE_4__ {scalar_t__ attr_mod; int /*<<< orphan*/  status; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_PMA_CONG_HW_CONTROL_SAMPLE ; 
 scalar_t__ IB_PMA_CONG_HW_CONTROL_TIMER ; 
 scalar_t__ IB_PMA_SAMPLE_STATUS_DONE ; 
 scalar_t__ IB_PMA_SAMPLE_STATUS_RUNNING ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  QIBPORTCNTR_PSSTAT ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct qib_devdata* dd_from_dev (struct qib_ibdev*) ; 
 int pma_get_portsamplescontrol (struct ib_pma_mad*,struct ib_device*,scalar_t__) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int reply (struct ib_smp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qib_pportdata*,void*,void*) ; 
 struct qib_ibdev* to_idev (struct ib_device*) ; 
 struct qib_ibport* to_iport (struct ib_device*,scalar_t__) ; 

__attribute__((used)) static int pma_set_portsamplescontrol(struct ib_pma_mad *pmp,
				      struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portsamplescontrol *p =
		(struct ib_pma_portsamplescontrol *)pmp->data;
	struct qib_ibdev *dev = to_idev(ibdev);
	struct qib_devdata *dd = dd_from_dev(dev);
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	unsigned long flags;
	u8 status, xmit_flags;
	int ret;

	if (pmp->mad_hdr.attr_mod != 0 || p->port_select != port) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		ret = reply((struct ib_smp *) pmp);
		goto bail;
	}

	spin_lock_irqsave(&ibp->rvp.lock, flags);

	/* Port Sampling code owns the PS* HW counters */
	xmit_flags = ppd->cong_stats.flags;
	ppd->cong_stats.flags = IB_PMA_CONG_HW_CONTROL_SAMPLE;
	status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
	if (status == IB_PMA_SAMPLE_STATUS_DONE ||
	    (status == IB_PMA_SAMPLE_STATUS_RUNNING &&
	     xmit_flags == IB_PMA_CONG_HW_CONTROL_TIMER)) {
		ibp->rvp.pma_sample_start = be32_to_cpu(p->sample_start);
		ibp->rvp.pma_sample_interval = be32_to_cpu(p->sample_interval);
		ibp->rvp.pma_tag = be16_to_cpu(p->tag);
		ibp->rvp.pma_counter_select[0] = p->counter_select[0];
		ibp->rvp.pma_counter_select[1] = p->counter_select[1];
		ibp->rvp.pma_counter_select[2] = p->counter_select[2];
		ibp->rvp.pma_counter_select[3] = p->counter_select[3];
		ibp->rvp.pma_counter_select[4] = p->counter_select[4];
		dd->f_set_cntr_sample(ppd, ibp->rvp.pma_sample_interval,
				      ibp->rvp.pma_sample_start);
	}
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	ret = pma_get_portsamplescontrol(pmp, ibdev, port);

bail:
	return ret;
}