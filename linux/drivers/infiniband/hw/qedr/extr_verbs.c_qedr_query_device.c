#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qedr_device_attr {int max_mr; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  dev_ack_delay; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_qp_resp_rd_atomic_resc; int /*<<< orphan*/  max_qp_req_rd_atomic_resc; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_rqe; int /*<<< orphan*/  max_sqe; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_caps; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct qedr_dev {int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  rdma_ctx; struct qedr_device_attr attr; } ;
struct ib_udata {int dummy; } ;
struct ib_device_attr {int device_cap_flags; int max_mr; int max_map_per_fmr; int max_qp_init_rd_atom; int max_fast_reg_page_list_len; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int IB_DEVICE_CURR_QP_STATE_MOD ; 
 int IB_DEVICE_LOCAL_DMA_LKEY ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int /*<<< orphan*/  QEDR_ROCE_PKEY_MAX ; 
 int fls (int /*<<< orphan*/ ) ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  u32 ; 

int qedr_query_device(struct ib_device *ibdev,
		      struct ib_device_attr *attr, struct ib_udata *udata)
{
	struct qedr_dev *dev = get_qedr_dev(ibdev);
	struct qedr_device_attr *qattr = &dev->attr;

	if (!dev->rdma_ctx) {
		DP_ERR(dev,
		       "qedr_query_device called with invalid params rdma_ctx=%p\n",
		       dev->rdma_ctx);
		return -EINVAL;
	}

	memset(attr, 0, sizeof(*attr));

	attr->fw_ver = qattr->fw_ver;
	attr->sys_image_guid = qattr->sys_image_guid;
	attr->max_mr_size = qattr->max_mr_size;
	attr->page_size_cap = qattr->page_size_caps;
	attr->vendor_id = qattr->vendor_id;
	attr->vendor_part_id = qattr->vendor_part_id;
	attr->hw_ver = qattr->hw_ver;
	attr->max_qp = qattr->max_qp;
	attr->max_qp_wr = max_t(u32, qattr->max_sqe, qattr->max_rqe);
	attr->device_cap_flags = IB_DEVICE_CURR_QP_STATE_MOD |
	    IB_DEVICE_RC_RNR_NAK_GEN |
	    IB_DEVICE_LOCAL_DMA_LKEY | IB_DEVICE_MEM_MGT_EXTENSIONS;

	attr->max_send_sge = qattr->max_sge;
	attr->max_recv_sge = qattr->max_sge;
	attr->max_sge_rd = qattr->max_sge;
	attr->max_cq = qattr->max_cq;
	attr->max_cqe = qattr->max_cqe;
	attr->max_mr = qattr->max_mr;
	attr->max_mw = qattr->max_mw;
	attr->max_pd = qattr->max_pd;
	attr->atomic_cap = dev->atomic_cap;
	attr->max_fmr = qattr->max_fmr;
	attr->max_map_per_fmr = 16;
	attr->max_qp_init_rd_atom =
	    1 << (fls(qattr->max_qp_req_rd_atomic_resc) - 1);
	attr->max_qp_rd_atom =
	    min(1 << (fls(qattr->max_qp_resp_rd_atomic_resc) - 1),
		attr->max_qp_init_rd_atom);

	attr->max_srq = qattr->max_srq;
	attr->max_srq_sge = qattr->max_srq_sge;
	attr->max_srq_wr = qattr->max_srq_wr;

	attr->local_ca_ack_delay = qattr->dev_ack_delay;
	attr->max_fast_reg_page_list_len = qattr->max_mr / 8;
	attr->max_pkeys = QEDR_ROCE_PKEY_MAX;
	attr->max_ah = qattr->max_ah;

	return 0;
}