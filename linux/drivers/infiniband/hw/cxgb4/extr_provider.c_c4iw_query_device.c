#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_device_attr {int max_qp; int max_sge_rd; int max_cq; int /*<<< orphan*/  max_fast_reg_page_list_len; scalar_t__ local_ca_ack_delay; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; void* max_qp_rd_atom; void* max_qp_init_rd_atom; int /*<<< orphan*/  max_res_rd_atom; void* max_srq_sge; void* max_recv_sge; void* max_send_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_mr_size; void* vendor_part_id; void* vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  device_cap_flags; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  sys_image_guid; } ;
struct ib_device {int dummy; } ;
struct TYPE_15__ {scalar_t__ ulptx_memwrite_dsgl; TYPE_5__* vr; int /*<<< orphan*/  max_ordird_qp; int /*<<< orphan*/  max_ird_adapter; TYPE_2__* pdev; int /*<<< orphan*/  fw_vers; int /*<<< orphan*/  adapter_type; TYPE_1__** ports; } ;
struct TYPE_14__ {int /*<<< orphan*/  t4_max_cq_depth; int /*<<< orphan*/  t4_max_qp_depth; } ;
struct TYPE_16__ {TYPE_7__ lldi; TYPE_6__ hw_queue; } ;
struct c4iw_dev {TYPE_8__ rdev; int /*<<< orphan*/  device_cap_flags; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
struct TYPE_13__ {TYPE_4__ qp; TYPE_3__ srq; } ;
struct TYPE_10__ {scalar_t__ device; scalar_t__ vendor; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_CHIP_RELEASE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  T4_MAX_MR_SIZE ; 
 int /*<<< orphan*/  T4_MAX_NUM_PD ; 
 void* T4_MAX_RECV_SGE ; 
 int /*<<< orphan*/  T4_MAX_SEND_SGE ; 
 int /*<<< orphan*/  T4_MAX_WRITE_SGE ; 
 int /*<<< orphan*/  T4_PAGESIZE_MASK ; 
 int /*<<< orphan*/  c4iw_max_read_depth ; 
 int /*<<< orphan*/  c4iw_num_stags (TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_device*) ; 
 int /*<<< orphan*/  t4_max_fr_depth (int) ; 
 struct c4iw_dev* to_c4iw_dev (struct ib_device*) ; 
 scalar_t__ use_dsgl ; 

__attribute__((used)) static int c4iw_query_device(struct ib_device *ibdev, struct ib_device_attr *props,
			     struct ib_udata *uhw)
{

	struct c4iw_dev *dev;

	pr_debug("ibdev %p\n", ibdev);

	if (uhw->inlen || uhw->outlen)
		return -EINVAL;

	dev = to_c4iw_dev(ibdev);
	memcpy(&props->sys_image_guid, dev->rdev.lldi.ports[0]->dev_addr, 6);
	props->hw_ver = CHELSIO_CHIP_RELEASE(dev->rdev.lldi.adapter_type);
	props->fw_ver = dev->rdev.lldi.fw_vers;
	props->device_cap_flags = dev->device_cap_flags;
	props->page_size_cap = T4_PAGESIZE_MASK;
	props->vendor_id = (u32)dev->rdev.lldi.pdev->vendor;
	props->vendor_part_id = (u32)dev->rdev.lldi.pdev->device;
	props->max_mr_size = T4_MAX_MR_SIZE;
	props->max_qp = dev->rdev.lldi.vr->qp.size / 2;
	props->max_srq = dev->rdev.lldi.vr->srq.size;
	props->max_qp_wr = dev->rdev.hw_queue.t4_max_qp_depth;
	props->max_srq_wr = dev->rdev.hw_queue.t4_max_qp_depth;
	props->max_send_sge = min(T4_MAX_SEND_SGE, T4_MAX_WRITE_SGE);
	props->max_recv_sge = T4_MAX_RECV_SGE;
	props->max_srq_sge = T4_MAX_RECV_SGE;
	props->max_sge_rd = 1;
	props->max_res_rd_atom = dev->rdev.lldi.max_ird_adapter;
	props->max_qp_rd_atom = min(dev->rdev.lldi.max_ordird_qp,
				    c4iw_max_read_depth);
	props->max_qp_init_rd_atom = props->max_qp_rd_atom;
	props->max_cq = dev->rdev.lldi.vr->qp.size;
	props->max_cqe = dev->rdev.hw_queue.t4_max_cq_depth;
	props->max_mr = c4iw_num_stags(&dev->rdev);
	props->max_pd = T4_MAX_NUM_PD;
	props->local_ca_ack_delay = 0;
	props->max_fast_reg_page_list_len =
		t4_max_fr_depth(dev->rdev.lldi.ulptx_memwrite_dsgl && use_dsgl);

	return 0;
}