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
typedef  int /*<<< orphan*/  u8 ;
struct ib_udata {int dummy; } ;
struct ib_device_attr {int page_size_cap; int device_cap_flags; int max_pkeys; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_fast_reg_page_list_len; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; scalar_t__ max_map_per_fmr; scalar_t__ max_fmr; int /*<<< orphan*/  max_ah; scalar_t__ max_total_mcast_qp_attach; scalar_t__ max_mcast_qp_attach; scalar_t__ max_mcast_grp; int /*<<< orphan*/  max_raw_ethy_qp; scalar_t__ max_raw_ipv6_qp; int /*<<< orphan*/  max_mw; scalar_t__ max_rdd; scalar_t__ max_ee; scalar_t__ max_ee_init_rd_atom; scalar_t__ max_res_rd_atom; scalar_t__ max_ee_rd_atom; void* masked_atomic_cap; void* atomic_cap; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;
struct bnxt_qplib_dev_attr {int /*<<< orphan*/  max_srq_sges; int /*<<< orphan*/  max_srq_wqes; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_raw_ethy_qp; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cq_wqes; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_qp_sges; int /*<<< orphan*/  max_qp_wqes; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  fw_ver; } ;
struct bnxt_re_dev {TYPE_3__* en_dev; TYPE_1__* netdev; struct bnxt_qplib_dev_attr dev_attr; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_RE_DEFAULT_ACK_DELAY ; 
 int /*<<< orphan*/  BNXT_RE_MAX_MR_SIZE ; 
 int BNXT_RE_PAGE_SIZE_2M ; 
 int BNXT_RE_PAGE_SIZE_4K ; 
 void* IB_ATOMIC_NONE ; 
 int IB_DEVICE_CURR_QP_STATE_MOD ; 
 int IB_DEVICE_LOCAL_DMA_LKEY ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_MEM_WINDOW ; 
 int IB_DEVICE_MEM_WINDOW_TYPE_2B ; 
 int IB_DEVICE_N_NOTIFY_CQ ; 
 int IB_DEVICE_PORT_ACTIVE_EVENT ; 
 int IB_DEVICE_RC_RNR_NAK_GEN ; 
 int IB_DEVICE_RESIZE_MAX_WR ; 
 int IB_DEVICE_SHUTDOWN_PORT ; 
 int IB_DEVICE_SYS_IMAGE_GUID ; 
 int /*<<< orphan*/  MAX_PBL_LVL_1_PGS ; 
 int /*<<< orphan*/  bnxt_qplib_get_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 struct bnxt_re_dev* to_bnxt_re_dev (struct ib_device*,struct ib_device*) ; 

int bnxt_re_query_device(struct ib_device *ibdev,
			 struct ib_device_attr *ib_attr,
			 struct ib_udata *udata)
{
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	struct bnxt_qplib_dev_attr *dev_attr = &rdev->dev_attr;

	memset(ib_attr, 0, sizeof(*ib_attr));
	memcpy(&ib_attr->fw_ver, dev_attr->fw_ver,
	       min(sizeof(dev_attr->fw_ver),
		   sizeof(ib_attr->fw_ver)));
	bnxt_qplib_get_guid(rdev->netdev->dev_addr,
			    (u8 *)&ib_attr->sys_image_guid);
	ib_attr->max_mr_size = BNXT_RE_MAX_MR_SIZE;
	ib_attr->page_size_cap = BNXT_RE_PAGE_SIZE_4K | BNXT_RE_PAGE_SIZE_2M;

	ib_attr->vendor_id = rdev->en_dev->pdev->vendor;
	ib_attr->vendor_part_id = rdev->en_dev->pdev->device;
	ib_attr->hw_ver = rdev->en_dev->pdev->subsystem_device;
	ib_attr->max_qp = dev_attr->max_qp;
	ib_attr->max_qp_wr = dev_attr->max_qp_wqes;
	ib_attr->device_cap_flags =
				    IB_DEVICE_CURR_QP_STATE_MOD
				    | IB_DEVICE_RC_RNR_NAK_GEN
				    | IB_DEVICE_SHUTDOWN_PORT
				    | IB_DEVICE_SYS_IMAGE_GUID
				    | IB_DEVICE_LOCAL_DMA_LKEY
				    | IB_DEVICE_RESIZE_MAX_WR
				    | IB_DEVICE_PORT_ACTIVE_EVENT
				    | IB_DEVICE_N_NOTIFY_CQ
				    | IB_DEVICE_MEM_WINDOW
				    | IB_DEVICE_MEM_WINDOW_TYPE_2B
				    | IB_DEVICE_MEM_MGT_EXTENSIONS;
	ib_attr->max_send_sge = dev_attr->max_qp_sges;
	ib_attr->max_recv_sge = dev_attr->max_qp_sges;
	ib_attr->max_sge_rd = dev_attr->max_qp_sges;
	ib_attr->max_cq = dev_attr->max_cq;
	ib_attr->max_cqe = dev_attr->max_cq_wqes;
	ib_attr->max_mr = dev_attr->max_mr;
	ib_attr->max_pd = dev_attr->max_pd;
	ib_attr->max_qp_rd_atom = dev_attr->max_qp_rd_atom;
	ib_attr->max_qp_init_rd_atom = dev_attr->max_qp_init_rd_atom;
	ib_attr->atomic_cap = IB_ATOMIC_NONE;
	ib_attr->masked_atomic_cap = IB_ATOMIC_NONE;

	ib_attr->max_ee_rd_atom = 0;
	ib_attr->max_res_rd_atom = 0;
	ib_attr->max_ee_init_rd_atom = 0;
	ib_attr->max_ee = 0;
	ib_attr->max_rdd = 0;
	ib_attr->max_mw = dev_attr->max_mw;
	ib_attr->max_raw_ipv6_qp = 0;
	ib_attr->max_raw_ethy_qp = dev_attr->max_raw_ethy_qp;
	ib_attr->max_mcast_grp = 0;
	ib_attr->max_mcast_qp_attach = 0;
	ib_attr->max_total_mcast_qp_attach = 0;
	ib_attr->max_ah = dev_attr->max_ah;

	ib_attr->max_fmr = 0;
	ib_attr->max_map_per_fmr = 0;

	ib_attr->max_srq = dev_attr->max_srq;
	ib_attr->max_srq_wr = dev_attr->max_srq_wqes;
	ib_attr->max_srq_sge = dev_attr->max_srq_sges;

	ib_attr->max_fast_reg_page_list_len = MAX_PBL_LVL_1_PGS;

	ib_attr->max_pkeys = 1;
	ib_attr->local_ca_ack_delay = BNXT_RE_DEFAULT_ACK_DELAY;
	return 0;
}