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
struct qed_int_info {int /*<<< orphan*/  msix_cnt; int /*<<< orphan*/ * msix; } ;
struct TYPE_3__ {scalar_t__ int_mode; } ;
struct TYPE_4__ {int rdma_msix_base; int /*<<< orphan*/ * msix_table; int /*<<< orphan*/  rdma_msix_cnt; TYPE_1__ out; int /*<<< orphan*/  fp_initialized; } ;
struct qed_dev {TYPE_2__ int_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 scalar_t__ QED_INT_MODE_MSIX ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  memset (struct qed_int_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_rdma_get_int(struct qed_dev *cdev, struct qed_int_info *info)
{
	memset(info, 0, sizeof(*info));

	if (!cdev->int_params.fp_initialized) {
		DP_INFO(cdev,
			"Protocol driver requested interrupt information, but its support is not yet configured\n");
		return -EINVAL;
	}

	if (cdev->int_params.out.int_mode == QED_INT_MODE_MSIX) {
		int msix_base = cdev->int_params.rdma_msix_base;

		info->msix_cnt = cdev->int_params.rdma_msix_cnt;
		info->msix = &cdev->int_params.msix_table[msix_base];

		DP_VERBOSE(cdev, QED_MSG_RDMA, "msix_cnt = %d msix_base=%d\n",
			   info->msix_cnt, msix_base);
	}

	return 0;
}