#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct qib_pportdata {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pma_counter_select; int /*<<< orphan*/  pma_tag; int /*<<< orphan*/  pma_sample_interval; int /*<<< orphan*/  pma_sample_start; } ;
struct qib_ibport {TYPE_2__ rvp; } ;
struct qib_ibdev {int dummy; } ;
struct qib_devdata {int /*<<< orphan*/  (* f_portcntr ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* f_get_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ) ;} ;
struct ib_smp {int dummy; } ;
struct ib_pma_portsamplescontrol {scalar_t__ port_select; int counter_width; int /*<<< orphan*/ * counter_select; int /*<<< orphan*/  tag; void* sample_interval; void* sample_start; int /*<<< orphan*/  counter_mask0_9; int /*<<< orphan*/  sample_status; int /*<<< orphan*/  tick; } ;
struct TYPE_3__ {scalar_t__ attr_mod; int /*<<< orphan*/  status; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_MASK0_9 ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int /*<<< orphan*/  QIBPORTCNTR_PSSTAT ; 
 int /*<<< orphan*/  QIB_IB_CFG_PMA_TICKS ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct qib_devdata* dd_from_dev (struct qib_ibdev*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int reply (struct ib_smp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 struct qib_ibdev* to_idev (struct ib_device*) ; 
 struct qib_ibport* to_iport (struct ib_device*,scalar_t__) ; 

__attribute__((used)) static int pma_get_portsamplescontrol(struct ib_pma_mad *pmp,
				      struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portsamplescontrol *p =
		(struct ib_pma_portsamplescontrol *)pmp->data;
	struct qib_ibdev *dev = to_idev(ibdev);
	struct qib_devdata *dd = dd_from_dev(dev);
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	unsigned long flags;
	u8 port_select = p->port_select;

	memset(pmp->data, 0, sizeof(pmp->data));

	p->port_select = port_select;
	if (pmp->mad_hdr.attr_mod != 0 || port_select != port) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		goto bail;
	}
	spin_lock_irqsave(&ibp->rvp.lock, flags);
	p->tick = dd->f_get_ib_cfg(ppd, QIB_IB_CFG_PMA_TICKS);
	p->sample_status = dd->f_portcntr(ppd, QIBPORTCNTR_PSSTAT);
	p->counter_width = 4;   /* 32 bit counters */
	p->counter_mask0_9 = COUNTER_MASK0_9;
	p->sample_start = cpu_to_be32(ibp->rvp.pma_sample_start);
	p->sample_interval = cpu_to_be32(ibp->rvp.pma_sample_interval);
	p->tag = cpu_to_be16(ibp->rvp.pma_tag);
	p->counter_select[0] = ibp->rvp.pma_counter_select[0];
	p->counter_select[1] = ibp->rvp.pma_counter_select[1];
	p->counter_select[2] = ibp->rvp.pma_counter_select[2];
	p->counter_select[3] = ibp->rvp.pma_counter_select[3];
	p->counter_select[4] = ibp->rvp.pma_counter_select[4];
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

bail:
	return reply((struct ib_smp *) pmp);
}