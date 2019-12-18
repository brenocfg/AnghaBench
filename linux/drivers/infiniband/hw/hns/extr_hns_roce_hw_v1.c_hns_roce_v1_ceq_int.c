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
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_eq {int cons_index; TYPE_3__* hr_dev; } ;
struct TYPE_4__ {int ceqe_depth; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
struct hns_roce_ceqe {int /*<<< orphan*/  comp; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EQ_DEPTH_COEFF ; 
 int /*<<< orphan*/  HNS_ROCE_CEQE_CEQE_COMP_CQN_M ; 
 int /*<<< orphan*/  HNS_ROCE_CEQE_CEQE_COMP_CQN_S ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  hns_roce_cq_completion (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 struct hns_roce_ceqe* next_ceqe_sw_v1 (struct hns_roce_eq*) ; 
 int /*<<< orphan*/  roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_eq_cons_index_v1 (struct hns_roce_eq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v1_ceq_int(struct hns_roce_dev *hr_dev,
			       struct hns_roce_eq *eq)
{
	struct hns_roce_ceqe *ceqe;
	int ceqes_found = 0;
	u32 cqn;

	while ((ceqe = next_ceqe_sw_v1(eq))) {

		/* Make sure we read CEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		cqn = roce_get_field(ceqe->comp,
				     HNS_ROCE_CEQE_CEQE_COMP_CQN_M,
				     HNS_ROCE_CEQE_CEQE_COMP_CQN_S);
		hns_roce_cq_completion(hr_dev, cqn);

		++eq->cons_index;
		ceqes_found = 1;

		if (eq->cons_index >
		    EQ_DEPTH_COEFF * hr_dev->caps.ceqe_depth - 1) {
			dev_warn(&eq->hr_dev->pdev->dev,
				"cons_index overflow, set back to 0.\n");
			eq->cons_index = 0;
		}
	}

	set_eq_cons_index_v1(eq, 0);

	return ceqes_found;
}