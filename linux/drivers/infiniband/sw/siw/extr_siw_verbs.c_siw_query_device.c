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
struct TYPE_3__ {int max_qp; int max_ird; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_ord; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; } ;
struct siw_device {TYPE_2__* netdev; int /*<<< orphan*/  vendor_part_id; TYPE_1__ attrs; } ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_device_attr {int device_cap_flags; unsigned long long max_mr_size; int max_qp; int max_qp_init_rd_atom; int max_res_rd_atom; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_fast_reg_page_list_len; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; scalar_t__ atomic_cap; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_DEVICE_ALLOW_USER_UNREG ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SIW_MAX_SGE_PBL ; 
 int /*<<< orphan*/  SIW_VENDOR_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 struct siw_device* to_siw_dev (struct ib_device*) ; 

int siw_query_device(struct ib_device *base_dev, struct ib_device_attr *attr,
		     struct ib_udata *udata)
{
	struct siw_device *sdev = to_siw_dev(base_dev);

	if (udata->inlen || udata->outlen)
		return -EINVAL;

	memset(attr, 0, sizeof(*attr));

	/* Revisit atomic caps if RFC 7306 gets supported */
	attr->atomic_cap = 0;
	attr->device_cap_flags =
		IB_DEVICE_MEM_MGT_EXTENSIONS | IB_DEVICE_ALLOW_USER_UNREG;
	attr->max_cq = sdev->attrs.max_cq;
	attr->max_cqe = sdev->attrs.max_cqe;
	attr->max_fast_reg_page_list_len = SIW_MAX_SGE_PBL;
	attr->max_fmr = sdev->attrs.max_fmr;
	attr->max_mr = sdev->attrs.max_mr;
	attr->max_mw = sdev->attrs.max_mw;
	attr->max_mr_size = ~0ull;
	attr->max_pd = sdev->attrs.max_pd;
	attr->max_qp = sdev->attrs.max_qp;
	attr->max_qp_init_rd_atom = sdev->attrs.max_ird;
	attr->max_qp_rd_atom = sdev->attrs.max_ord;
	attr->max_qp_wr = sdev->attrs.max_qp_wr;
	attr->max_recv_sge = sdev->attrs.max_sge;
	attr->max_res_rd_atom = sdev->attrs.max_qp * sdev->attrs.max_ird;
	attr->max_send_sge = sdev->attrs.max_sge;
	attr->max_sge_rd = sdev->attrs.max_sge_rd;
	attr->max_srq = sdev->attrs.max_srq;
	attr->max_srq_sge = sdev->attrs.max_srq_sge;
	attr->max_srq_wr = sdev->attrs.max_srq_wr;
	attr->page_size_cap = PAGE_SIZE;
	attr->vendor_id = SIW_VENDOR_ID;
	attr->vendor_part_id = sdev->vendor_part_id;

	memcpy(&attr->sys_image_guid, sdev->netdev->dev_addr, 6);

	return 0;
}