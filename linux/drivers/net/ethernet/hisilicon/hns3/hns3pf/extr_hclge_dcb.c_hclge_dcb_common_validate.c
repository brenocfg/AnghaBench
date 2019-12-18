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
typedef  int /*<<< orphan*/  u8 ;
struct hclge_dev {TYPE_2__* vport; TYPE_1__* pdev; int /*<<< orphan*/  tc_max; } ;
struct TYPE_4__ {int /*<<< orphan*/  alloc_tqps; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int HNAE3_MAX_USER_PRIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int hclge_dcb_common_validate(struct hclge_dev *hdev, u8 num_tc,
				     u8 *prio_tc)
{
	int i;

	if (num_tc > hdev->tc_max) {
		dev_err(&hdev->pdev->dev,
			"tc num checking failed, %u > tc_max(%u)\n",
			num_tc, hdev->tc_max);
		return -EINVAL;
	}

	for (i = 0; i < HNAE3_MAX_USER_PRIO; i++) {
		if (prio_tc[i] >= num_tc) {
			dev_err(&hdev->pdev->dev,
				"prio_tc[%u] checking failed, %u >= num_tc(%u)\n",
				i, prio_tc[i], num_tc);
			return -EINVAL;
		}
	}

	if (num_tc > hdev->vport[0].alloc_tqps) {
		dev_err(&hdev->pdev->dev,
			"allocated tqp checking failed, %u > tqp(%u)\n",
			num_tc, hdev->vport[0].alloc_tqps);
		return -EINVAL;
	}

	return 0;
}