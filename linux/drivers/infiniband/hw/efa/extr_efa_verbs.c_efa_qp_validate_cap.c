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
struct TYPE_3__ {scalar_t__ max_send_wr; scalar_t__ max_recv_wr; scalar_t__ max_send_sge; scalar_t__ max_recv_sge; scalar_t__ max_inline_data; } ;
struct ib_qp_init_attr {TYPE_1__ cap; } ;
struct TYPE_4__ {scalar_t__ max_sq_depth; scalar_t__ max_rq_depth; scalar_t__ max_sq_sge; scalar_t__ max_rq_sge; scalar_t__ inline_buf_size; } ;
struct efa_dev {TYPE_2__ dev_attr; int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int efa_qp_validate_cap(struct efa_dev *dev,
			       struct ib_qp_init_attr *init_attr)
{
	if (init_attr->cap.max_send_wr > dev->dev_attr.max_sq_depth) {
		ibdev_dbg(&dev->ibdev,
			  "qp: requested send wr[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_send_wr,
			  dev->dev_attr.max_sq_depth);
		return -EINVAL;
	}
	if (init_attr->cap.max_recv_wr > dev->dev_attr.max_rq_depth) {
		ibdev_dbg(&dev->ibdev,
			  "qp: requested receive wr[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_recv_wr,
			  dev->dev_attr.max_rq_depth);
		return -EINVAL;
	}
	if (init_attr->cap.max_send_sge > dev->dev_attr.max_sq_sge) {
		ibdev_dbg(&dev->ibdev,
			  "qp: requested sge send[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_send_sge, dev->dev_attr.max_sq_sge);
		return -EINVAL;
	}
	if (init_attr->cap.max_recv_sge > dev->dev_attr.max_rq_sge) {
		ibdev_dbg(&dev->ibdev,
			  "qp: requested sge recv[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_recv_sge, dev->dev_attr.max_rq_sge);
		return -EINVAL;
	}
	if (init_attr->cap.max_inline_data > dev->dev_attr.inline_buf_size) {
		ibdev_dbg(&dev->ibdev,
			  "qp: requested inline data[%u] exceeds the max[%u]\n",
			  init_attr->cap.max_inline_data,
			  dev->dev_attr.inline_buf_size);
		return -EINVAL;
	}

	return 0;
}