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
struct qedr_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_recv_sge; scalar_t__ max_recv_wr; scalar_t__ max_send_wr; } ;
struct ib_qp_init_attr {TYPE_1__ cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ QEDR_GSI_MAX_RECV_SGE ; 
 scalar_t__ QEDR_GSI_MAX_RECV_WR ; 
 scalar_t__ QEDR_GSI_MAX_SEND_WR ; 

__attribute__((used)) static inline int qedr_check_gsi_qp_attrs(struct qedr_dev *dev,
					  struct ib_qp_init_attr *attrs)
{
	if (attrs->cap.max_recv_sge > QEDR_GSI_MAX_RECV_SGE) {
		DP_ERR(dev,
		       " create gsi qp: failed. max_recv_sge is larger the max %d>%d\n",
		       attrs->cap.max_recv_sge, QEDR_GSI_MAX_RECV_SGE);
		return -EINVAL;
	}

	if (attrs->cap.max_recv_wr > QEDR_GSI_MAX_RECV_WR) {
		DP_ERR(dev,
		       " create gsi qp: failed. max_recv_wr is too large %d>%d\n",
		       attrs->cap.max_recv_wr, QEDR_GSI_MAX_RECV_WR);
		return -EINVAL;
	}

	if (attrs->cap.max_send_wr > QEDR_GSI_MAX_SEND_WR) {
		DP_ERR(dev,
		       " create gsi qp: failed. max_send_wr is too large %d>%d\n",
		       attrs->cap.max_send_wr, QEDR_GSI_MAX_SEND_WR);
		return -EINVAL;
	}

	return 0;
}