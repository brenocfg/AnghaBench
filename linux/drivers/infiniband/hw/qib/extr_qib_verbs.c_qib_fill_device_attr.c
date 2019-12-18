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
struct TYPE_6__ {int device_cap_flags; int vendor_id; unsigned long long max_mr_size; int max_map_per_fmr; int max_qp_init_rd_atom; int max_mcast_grp; int max_mcast_qp_attach; int max_total_mcast_qp_attach; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_qp_rd_atom; void* max_ah; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; void* max_sge_rd; void* max_recv_sge; void* max_send_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_pd; } ;
struct TYPE_4__ {TYPE_3__ props; } ;
struct rvt_dev_info {int /*<<< orphan*/  wc_opcode; int /*<<< orphan*/  post_parms; TYPE_1__ dparms; } ;
struct TYPE_5__ {struct rvt_dev_info rdi; } ;
struct qib_devdata {TYPE_2__ verbs_dev; int /*<<< orphan*/  minrev; int /*<<< orphan*/  deviceid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ATOMIC_GLOB ; 
 int IB_DEVICE_BAD_PKEY_CNTR ; 
 int IB_DEVICE_BAD_QKEY_CNTR ; 
 int IB_DEVICE_PORT_ACTIVE_EVENT ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int IB_DEVICE_SHUTDOWN_PORT ; 
 int IB_DEVICE_SRQ_RESIZE ; 
 int IB_DEVICE_SYS_IMAGE_GUID ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  QIB_MAX_RDMA_ATOMIC ; 
 int QIB_SRC_OUI_1 ; 
 int QIB_SRC_OUI_2 ; 
 int QIB_SRC_OUI_3 ; 
 void* ib_qib_max_ahs ; 
 int /*<<< orphan*/  ib_qib_max_cqes ; 
 int /*<<< orphan*/  ib_qib_max_cqs ; 
 int ib_qib_max_mcast_grps ; 
 int ib_qib_max_mcast_qp_attached ; 
 int /*<<< orphan*/  ib_qib_max_pds ; 
 int /*<<< orphan*/  ib_qib_max_qp_wrs ; 
 int /*<<< orphan*/  ib_qib_max_qps ; 
 void* ib_qib_max_sges ; 
 int /*<<< orphan*/  ib_qib_max_srq_sges ; 
 int /*<<< orphan*/  ib_qib_max_srq_wrs ; 
 int /*<<< orphan*/  ib_qib_max_srqs ; 
 int /*<<< orphan*/  ib_qib_sys_image_guid ; 
 int /*<<< orphan*/  ib_qib_wc_opcode ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_get_npkeys (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_post_parms ; 

__attribute__((used)) static void qib_fill_device_attr(struct qib_devdata *dd)
{
	struct rvt_dev_info *rdi = &dd->verbs_dev.rdi;

	memset(&rdi->dparms.props, 0, sizeof(rdi->dparms.props));

	rdi->dparms.props.max_pd = ib_qib_max_pds;
	rdi->dparms.props.max_ah = ib_qib_max_ahs;
	rdi->dparms.props.device_cap_flags = IB_DEVICE_BAD_PKEY_CNTR |
		IB_DEVICE_BAD_QKEY_CNTR | IB_DEVICE_SHUTDOWN_PORT |
		IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_RC_RNR_NAK_GEN |
		IB_DEVICE_PORT_ACTIVE_EVENT | IB_DEVICE_SRQ_RESIZE;
	rdi->dparms.props.page_size_cap = PAGE_SIZE;
	rdi->dparms.props.vendor_id =
		QIB_SRC_OUI_1 << 16 | QIB_SRC_OUI_2 << 8 | QIB_SRC_OUI_3;
	rdi->dparms.props.vendor_part_id = dd->deviceid;
	rdi->dparms.props.hw_ver = dd->minrev;
	rdi->dparms.props.sys_image_guid = ib_qib_sys_image_guid;
	rdi->dparms.props.max_mr_size = ~0ULL;
	rdi->dparms.props.max_qp = ib_qib_max_qps;
	rdi->dparms.props.max_qp_wr = ib_qib_max_qp_wrs;
	rdi->dparms.props.max_send_sge = ib_qib_max_sges;
	rdi->dparms.props.max_recv_sge = ib_qib_max_sges;
	rdi->dparms.props.max_sge_rd = ib_qib_max_sges;
	rdi->dparms.props.max_cq = ib_qib_max_cqs;
	rdi->dparms.props.max_cqe = ib_qib_max_cqes;
	rdi->dparms.props.max_ah = ib_qib_max_ahs;
	rdi->dparms.props.max_map_per_fmr = 32767;
	rdi->dparms.props.max_qp_rd_atom = QIB_MAX_RDMA_ATOMIC;
	rdi->dparms.props.max_qp_init_rd_atom = 255;
	rdi->dparms.props.max_srq = ib_qib_max_srqs;
	rdi->dparms.props.max_srq_wr = ib_qib_max_srq_wrs;
	rdi->dparms.props.max_srq_sge = ib_qib_max_srq_sges;
	rdi->dparms.props.atomic_cap = IB_ATOMIC_GLOB;
	rdi->dparms.props.max_pkeys = qib_get_npkeys(dd);
	rdi->dparms.props.max_mcast_grp = ib_qib_max_mcast_grps;
	rdi->dparms.props.max_mcast_qp_attach = ib_qib_max_mcast_qp_attached;
	rdi->dparms.props.max_total_mcast_qp_attach =
					rdi->dparms.props.max_mcast_qp_attach *
					rdi->dparms.props.max_mcast_grp;
	/* post send table */
	dd->verbs_dev.rdi.post_parms = qib_post_parms;

	/* opcode translation table */
	dd->verbs_dev.rdi.wc_opcode = ib_qib_wc_opcode;
}