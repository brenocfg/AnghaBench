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
struct TYPE_4__ {struct ib_mad_agent* send_agent; } ;
struct qib_ibport {TYPE_3__* smi_ah; TYPE_1__ rvp; } ;
struct qib_pportdata {TYPE_2__* cpspec; struct qib_ibport ibport_data; } ;
struct ib_smp {int class_version; int hop_cnt; scalar_t__ attr_mod; int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; int /*<<< orphan*/  mgmt_class; int /*<<< orphan*/  base_version; } ;
struct ib_mad_send_buf {struct ib_smp* mad; struct ib_mad_send_buf* ah; } ;
struct ib_mad_agent {int dummy; } ;
struct ib_ah {struct ib_smp* mad; struct ib_ah* ah; } ;
struct TYPE_6__ {struct ib_mad_send_buf ibah; } ;
struct TYPE_5__ {int ipg_tries; int /*<<< orphan*/  ipg_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int /*<<< orphan*/  IB_MGMT_BASE_VERSION ; 
 int /*<<< orphan*/  IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 int /*<<< orphan*/  IB_MGMT_MAD_DATA ; 
 int /*<<< orphan*/  IB_MGMT_MAD_HDR ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_SEND ; 
 scalar_t__ IS_ERR (struct ib_mad_send_buf*) ; 
 int PTR_ERR (struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  QIB_VENDOR_IPG ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ib_mad_send_buf* ib_create_send_mad (struct ib_mad_agent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_free_send_mad (struct ib_mad_send_buf*) ; 
 int ib_post_send_mad (struct ib_mad_send_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_wq ; 
 TYPE_3__* ibah_to_rvtah (struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 struct ib_mad_send_buf* qib_create_qp0_ah (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void try_7322_ipg(struct qib_pportdata *ppd)
{
	struct qib_ibport *ibp = &ppd->ibport_data;
	struct ib_mad_send_buf *send_buf;
	struct ib_mad_agent *agent;
	struct ib_smp *smp;
	unsigned delay;
	int ret;

	agent = ibp->rvp.send_agent;
	if (!agent)
		goto retry;

	send_buf = ib_create_send_mad(agent, 0, 0, 0, IB_MGMT_MAD_HDR,
				      IB_MGMT_MAD_DATA, GFP_ATOMIC,
				      IB_MGMT_BASE_VERSION);
	if (IS_ERR(send_buf))
		goto retry;

	if (!ibp->smi_ah) {
		struct ib_ah *ah;

		ah = qib_create_qp0_ah(ibp, be16_to_cpu(IB_LID_PERMISSIVE));
		if (IS_ERR(ah))
			ret = PTR_ERR(ah);
		else {
			send_buf->ah = ah;
			ibp->smi_ah = ibah_to_rvtah(ah);
			ret = 0;
		}
	} else {
		send_buf->ah = &ibp->smi_ah->ibah;
		ret = 0;
	}

	smp = send_buf->mad;
	smp->base_version = IB_MGMT_BASE_VERSION;
	smp->mgmt_class = IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE;
	smp->class_version = 1;
	smp->method = IB_MGMT_METHOD_SEND;
	smp->hop_cnt = 1;
	smp->attr_id = QIB_VENDOR_IPG;
	smp->attr_mod = 0;

	if (!ret)
		ret = ib_post_send_mad(send_buf, NULL);
	if (ret)
		ib_free_send_mad(send_buf);
retry:
	delay = 2 << ppd->cpspec->ipg_tries;
	queue_delayed_work(ib_wq, &ppd->cpspec->ipg_work,
			   msecs_to_jiffies(delay));
}