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
struct pvrdma_dev {TYPE_3__* dsr; TYPE_1__* pdev; } ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_device_attr {int device_cap_flags; void* max_fast_reg_page_list_len; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  masked_atomic_cap; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; void* max_sge_rd; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;
struct TYPE_5__ {int device_cap_flags; int atomic_ops; int bmme_flags; int /*<<< orphan*/  max_fast_reg_page_list_len; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct TYPE_6__ {TYPE_2__ caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_ATOMIC_HCA ; 
 int /*<<< orphan*/  IB_ATOMIC_NONE ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_PORT_ACTIVE_EVENT ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int PVRDMA_ATOMIC_OP_COMP_SWAP ; 
 int PVRDMA_ATOMIC_OP_FETCH_ADD ; 
 int PVRDMA_BMME_FLAG_FAST_REG_WR ; 
 int PVRDMA_BMME_FLAG_LOCAL_INV ; 
 int PVRDMA_BMME_FLAG_REMOTE_INV ; 
 void* PVRDMA_GET_CAP (struct pvrdma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVRDMA_MAX_FAST_REG_PAGES ; 
 struct pvrdma_dev* to_vdev (struct ib_device*) ; 

int pvrdma_query_device(struct ib_device *ibdev,
			struct ib_device_attr *props,
			struct ib_udata *uhw)
{
	struct pvrdma_dev *dev = to_vdev(ibdev);

	if (uhw->inlen || uhw->outlen)
		return -EINVAL;

	props->fw_ver = dev->dsr->caps.fw_ver;
	props->sys_image_guid = dev->dsr->caps.sys_image_guid;
	props->max_mr_size = dev->dsr->caps.max_mr_size;
	props->page_size_cap = dev->dsr->caps.page_size_cap;
	props->vendor_id = dev->dsr->caps.vendor_id;
	props->vendor_part_id = dev->pdev->device;
	props->hw_ver = dev->dsr->caps.hw_ver;
	props->max_qp = dev->dsr->caps.max_qp;
	props->max_qp_wr = dev->dsr->caps.max_qp_wr;
	props->device_cap_flags = dev->dsr->caps.device_cap_flags;
	props->max_send_sge = dev->dsr->caps.max_sge;
	props->max_recv_sge = dev->dsr->caps.max_sge;
	props->max_sge_rd = PVRDMA_GET_CAP(dev, dev->dsr->caps.max_sge,
					   dev->dsr->caps.max_sge_rd);
	props->max_srq = dev->dsr->caps.max_srq;
	props->max_srq_wr = dev->dsr->caps.max_srq_wr;
	props->max_srq_sge = dev->dsr->caps.max_srq_sge;
	props->max_cq = dev->dsr->caps.max_cq;
	props->max_cqe = dev->dsr->caps.max_cqe;
	props->max_mr = dev->dsr->caps.max_mr;
	props->max_pd = dev->dsr->caps.max_pd;
	props->max_qp_rd_atom = dev->dsr->caps.max_qp_rd_atom;
	props->max_qp_init_rd_atom = dev->dsr->caps.max_qp_init_rd_atom;
	props->atomic_cap =
		dev->dsr->caps.atomic_ops &
		(PVRDMA_ATOMIC_OP_COMP_SWAP | PVRDMA_ATOMIC_OP_FETCH_ADD) ?
		IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->masked_atomic_cap = props->atomic_cap;
	props->max_ah = dev->dsr->caps.max_ah;
	props->max_pkeys = dev->dsr->caps.max_pkeys;
	props->local_ca_ack_delay = dev->dsr->caps.local_ca_ack_delay;
	if ((dev->dsr->caps.bmme_flags & PVRDMA_BMME_FLAG_LOCAL_INV) &&
	    (dev->dsr->caps.bmme_flags & PVRDMA_BMME_FLAG_REMOTE_INV) &&
	    (dev->dsr->caps.bmme_flags & PVRDMA_BMME_FLAG_FAST_REG_WR)) {
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
		props->max_fast_reg_page_list_len = PVRDMA_GET_CAP(dev,
				PVRDMA_MAX_FAST_REG_PAGES,
				dev->dsr->caps.max_fast_reg_page_list_len);
	}

	props->device_cap_flags |= IB_DEVICE_PORT_ACTIVE_EVENT |
				   IB_DEVICE_RC_RNR_NAK_GEN;

	return 0;
}