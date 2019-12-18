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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ib_qp_cap {scalar_t__ max_send_sge; } ;
struct hns_roce_ib_create_qp {int log_sq_bb_count; scalar_t__ log_sq_stride; } ;
struct TYPE_2__ {scalar_t__ max_wqes; scalar_t__ max_sq_sg; int /*<<< orphan*/  max_sq_desc_sz; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNS_ROCE_IB_MIN_SQ_STRIDE ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ilog2 (scalar_t__) ; 
 scalar_t__ roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_sq_size_with_integrity(struct hns_roce_dev *hr_dev,
					struct ib_qp_cap *cap,
					struct hns_roce_ib_create_qp *ucmd)
{
	u32 roundup_sq_stride = roundup_pow_of_two(hr_dev->caps.max_sq_desc_sz);
	u8 max_sq_stride = ilog2(roundup_sq_stride);

	/* Sanity check SQ size before proceeding */
	if ((u32)(1 << ucmd->log_sq_bb_count) > hr_dev->caps.max_wqes ||
	     ucmd->log_sq_stride > max_sq_stride ||
	     ucmd->log_sq_stride < HNS_ROCE_IB_MIN_SQ_STRIDE) {
		ibdev_err(&hr_dev->ib_dev, "check SQ size error!\n");
		return -EINVAL;
	}

	if (cap->max_send_sge > hr_dev->caps.max_sq_sg) {
		ibdev_err(&hr_dev->ib_dev, "SQ sge error! max_send_sge=%d\n",
			  cap->max_send_sge);
		return -EINVAL;
	}

	return 0;
}