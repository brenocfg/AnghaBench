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
struct efa_com_get_device_attr_result {int admin_api_version; int /*<<< orphan*/  sub_cqs_per_cq; int /*<<< orphan*/  max_llq_size; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr_pages; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_rq_sge; int /*<<< orphan*/  max_sq_sge; int /*<<< orphan*/  inline_buf_size; int /*<<< orphan*/  max_cq_depth; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_rq_depth; int /*<<< orphan*/  max_sq_depth; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  db_bar; int /*<<< orphan*/  virt_addr_width; int /*<<< orphan*/  phys_addr_width; int /*<<< orphan*/  supported_features; int /*<<< orphan*/  device_version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  page_size_cap; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; int /*<<< orphan*/  supported_features; } ;
struct TYPE_5__ {int /*<<< orphan*/  sub_cqs_per_cq; int /*<<< orphan*/  max_llq_size; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr_pages; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_wr_recv_sges; int /*<<< orphan*/  max_wr_send_sges; int /*<<< orphan*/  inline_buf_size; int /*<<< orphan*/  max_cq_depth; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_rq_depth; int /*<<< orphan*/  max_sq_depth; int /*<<< orphan*/  max_qp; } ;
struct TYPE_4__ {int admin_api_version; int /*<<< orphan*/  supported_features; int /*<<< orphan*/  db_bar; int /*<<< orphan*/  virt_addr_width; int /*<<< orphan*/  phys_addr_width; int /*<<< orphan*/  device_version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  page_size_cap; } ;
struct TYPE_6__ {TYPE_2__ queue_attr; TYPE_1__ device_attr; } ;
struct efa_admin_get_feature_resp {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_DEVICE_ATTR ; 
 int /*<<< orphan*/  EFA_ADMIN_QUEUE_ATTR ; 
 int EINVAL ; 
 int efa_com_get_feature (struct efa_com_dev*,struct efa_admin_get_feature_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 

int efa_com_get_device_attr(struct efa_com_dev *edev,
			    struct efa_com_get_device_attr_result *result)
{
	struct efa_admin_get_feature_resp resp;
	int err;

	err = efa_com_get_feature(edev, &resp, EFA_ADMIN_DEVICE_ATTR);
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get device attributes %d\n",
				      err);
		return err;
	}

	result->page_size_cap = resp.u.device_attr.page_size_cap;
	result->fw_version = resp.u.device_attr.fw_version;
	result->admin_api_version = resp.u.device_attr.admin_api_version;
	result->device_version = resp.u.device_attr.device_version;
	result->supported_features = resp.u.device_attr.supported_features;
	result->phys_addr_width = resp.u.device_attr.phys_addr_width;
	result->virt_addr_width = resp.u.device_attr.virt_addr_width;
	result->db_bar = resp.u.device_attr.db_bar;

	if (result->admin_api_version < 1) {
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to get device attr api version [%u < 1]\n",
			result->admin_api_version);
		return -EINVAL;
	}

	edev->supported_features = resp.u.device_attr.supported_features;
	err = efa_com_get_feature(edev, &resp,
				  EFA_ADMIN_QUEUE_ATTR);
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to get queue attributes %d\n",
				      err);
		return err;
	}

	result->max_qp = resp.u.queue_attr.max_qp;
	result->max_sq_depth = resp.u.queue_attr.max_sq_depth;
	result->max_rq_depth = resp.u.queue_attr.max_rq_depth;
	result->max_cq = resp.u.queue_attr.max_cq;
	result->max_cq_depth = resp.u.queue_attr.max_cq_depth;
	result->inline_buf_size = resp.u.queue_attr.inline_buf_size;
	result->max_sq_sge = resp.u.queue_attr.max_wr_send_sges;
	result->max_rq_sge = resp.u.queue_attr.max_wr_recv_sges;
	result->max_mr = resp.u.queue_attr.max_mr;
	result->max_mr_pages = resp.u.queue_attr.max_mr_pages;
	result->max_pd = resp.u.queue_attr.max_pd;
	result->max_ah = resp.u.queue_attr.max_ah;
	result->max_llq_size = resp.u.queue_attr.max_llq_size;
	result->sub_cqs_per_cq = resp.u.queue_attr.sub_cqs_per_cq;

	return 0;
}