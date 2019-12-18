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
typedef  scalar_t__ u64 ;
struct ib_udata {int dummy; } ;
struct ib_device_attr {int device_cap_flags; int max_sge_rd; int max_pkeys; int /*<<< orphan*/  max_fast_reg_page_list_len; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; scalar_t__ max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  max_srq_sges; int /*<<< orphan*/  max_srq_wrs; int /*<<< orphan*/  max_srqs; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_qp_init_rdma; int /*<<< orphan*/  max_qp_dest_rdma; int /*<<< orphan*/  num_pds; int /*<<< orphan*/  num_mtpts; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  max_rq_sg; int /*<<< orphan*/  max_sq_sg; int /*<<< orphan*/  max_wqes; int /*<<< orphan*/  num_qps; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  fw_ver; } ;
struct hns_roce_dev {TYPE_1__ caps; int /*<<< orphan*/  hw_rev; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  sys_image_guid; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_ATOMIC ; 
 int HNS_ROCE_CAP_FLAG_FRMR ; 
 int HNS_ROCE_CAP_FLAG_SRQ ; 
 int /*<<< orphan*/  HNS_ROCE_FRMR_MAX_PA ; 
 int /*<<< orphan*/  IB_ATOMIC_HCA ; 
 int /*<<< orphan*/  IB_ATOMIC_NONE ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_PORT_ACTIVE_EVENT ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 struct hns_roce_dev* to_hr_dev (struct ib_device*) ; 

__attribute__((used)) static int hns_roce_query_device(struct ib_device *ib_dev,
				 struct ib_device_attr *props,
				 struct ib_udata *uhw)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_dev);

	memset(props, 0, sizeof(*props));

	props->fw_ver = hr_dev->caps.fw_ver;
	props->sys_image_guid = cpu_to_be64(hr_dev->sys_image_guid);
	props->max_mr_size = (u64)(~(0ULL));
	props->page_size_cap = hr_dev->caps.page_size_cap;
	props->vendor_id = hr_dev->vendor_id;
	props->vendor_part_id = hr_dev->vendor_part_id;
	props->hw_ver = hr_dev->hw_rev;
	props->max_qp = hr_dev->caps.num_qps;
	props->max_qp_wr = hr_dev->caps.max_wqes;
	props->device_cap_flags = IB_DEVICE_PORT_ACTIVE_EVENT |
				  IB_DEVICE_RC_RNR_NAK_GEN;
	props->max_send_sge = hr_dev->caps.max_sq_sg;
	props->max_recv_sge = hr_dev->caps.max_rq_sg;
	props->max_sge_rd = 1;
	props->max_cq = hr_dev->caps.num_cqs;
	props->max_cqe = hr_dev->caps.max_cqes;
	props->max_mr = hr_dev->caps.num_mtpts;
	props->max_pd = hr_dev->caps.num_pds;
	props->max_qp_rd_atom = hr_dev->caps.max_qp_dest_rdma;
	props->max_qp_init_rd_atom = hr_dev->caps.max_qp_init_rdma;
	props->atomic_cap = hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_ATOMIC ?
			    IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->max_pkeys = 1;
	props->local_ca_ack_delay = hr_dev->caps.local_ca_ack_delay;
	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ) {
		props->max_srq = hr_dev->caps.max_srqs;
		props->max_srq_wr = hr_dev->caps.max_srq_wrs;
		props->max_srq_sge = hr_dev->caps.max_srq_sges;
	}

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_FRMR) {
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
		props->max_fast_reg_page_list_len = HNS_ROCE_FRMR_MAX_PA;
	}

	return 0;
}