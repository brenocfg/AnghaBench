#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qed_rdma_start_in_params {int dummy; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int qed_rdma_start (int /*<<< orphan*/ ,struct qed_rdma_start_in_params*) ; 

__attribute__((used)) static int qed_rdma_init(struct qed_dev *cdev,
			 struct qed_rdma_start_in_params *params)
{
	return qed_rdma_start(QED_AFFIN_HWFN(cdev), params);
}