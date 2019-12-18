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
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_device_attr {int max_mr_size; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; } ;
struct ib_device {int dummy; } ;
struct efa_ibv_ex_query_device_resp {int /*<<< orphan*/  max_rq_wr; int /*<<< orphan*/  max_sq_wr; int /*<<< orphan*/  max_rq_sge; int /*<<< orphan*/  max_sq_sge; } ;
struct efa_com_get_device_attr_result {int max_mr_pages; int /*<<< orphan*/  max_rq_depth; int /*<<< orphan*/  max_sq_depth; int /*<<< orphan*/  max_rq_sge; int /*<<< orphan*/  max_sq_sge; int /*<<< orphan*/  max_cq_depth; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  page_size_cap; } ;
struct efa_dev {TYPE_1__* pdev; struct efa_com_get_device_attr_result dev_attr; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_2__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int ib_copy_to_udata (struct ib_udata*,struct efa_ibv_ex_query_device_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_is_udata_cleared (struct ib_udata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ibdev_dbg (struct ib_device*,char*) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,scalar_t__) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct efa_dev* to_edev (struct ib_device*) ; 
 int /*<<< orphan*/  u32 ; 

int efa_query_device(struct ib_device *ibdev,
		     struct ib_device_attr *props,
		     struct ib_udata *udata)
{
	struct efa_com_get_device_attr_result *dev_attr;
	struct efa_ibv_ex_query_device_resp resp = {};
	struct efa_dev *dev = to_edev(ibdev);
	int err;

	if (udata && udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) {
		ibdev_dbg(ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		return -EINVAL;
	}

	dev_attr = &dev->dev_attr;

	memset(props, 0, sizeof(*props));
	props->max_mr_size = dev_attr->max_mr_pages * PAGE_SIZE;
	props->page_size_cap = dev_attr->page_size_cap;
	props->vendor_id = dev->pdev->vendor;
	props->vendor_part_id = dev->pdev->device;
	props->hw_ver = dev->pdev->subsystem_device;
	props->max_qp = dev_attr->max_qp;
	props->max_cq = dev_attr->max_cq;
	props->max_pd = dev_attr->max_pd;
	props->max_mr = dev_attr->max_mr;
	props->max_ah = dev_attr->max_ah;
	props->max_cqe = dev_attr->max_cq_depth;
	props->max_qp_wr = min_t(u32, dev_attr->max_sq_depth,
				 dev_attr->max_rq_depth);
	props->max_send_sge = dev_attr->max_sq_sge;
	props->max_recv_sge = dev_attr->max_rq_sge;

	if (udata && udata->outlen) {
		resp.max_sq_sge = dev_attr->max_sq_sge;
		resp.max_rq_sge = dev_attr->max_rq_sge;
		resp.max_sq_wr = dev_attr->max_sq_depth;
		resp.max_rq_wr = dev_attr->max_rq_depth;

		err = ib_copy_to_udata(udata, &resp,
				       min(sizeof(resp), udata->outlen));
		if (err) {
			ibdev_dbg(ibdev,
				  "Failed to copy udata for query_device\n");
			return err;
		}
	}

	return 0;
}