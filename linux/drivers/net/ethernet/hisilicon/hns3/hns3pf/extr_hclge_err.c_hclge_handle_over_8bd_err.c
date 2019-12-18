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
typedef  int u16 ;
struct hclge_dev {int num_alloc_vport; TYPE_2__* vport; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int vport_id; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_FUNC_RESET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int hclge_inform_reset_assert_to_vf (TYPE_2__*) ; 
 int hclge_query_over_8bd_err_info (struct hclge_dev*,int*,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void hclge_handle_over_8bd_err(struct hclge_dev *hdev,
				      unsigned long *reset_requests)
{
	struct device *dev = &hdev->pdev->dev;
	u16 vf_id;
	u16 q_id;
	int ret;

	ret = hclge_query_over_8bd_err_info(hdev, &vf_id, &q_id);
	if (ret) {
		dev_err(dev, "fail(%d) to query over_8bd_no_fe info\n",
			ret);
		return;
	}

	dev_err(dev, "PPU_PF_ABNORMAL_INT_ST over_8bd_no_fe found, vf_id(%u), queue_id(%u)\n",
		vf_id, q_id);

	if (vf_id) {
		if (vf_id >= hdev->num_alloc_vport) {
			dev_err(dev, "invalid vf id(%d)\n", vf_id);
			return;
		}

		/* If we need to trigger other reset whose level is higher
		 * than HNAE3_VF_FUNC_RESET, no need to trigger a VF reset
		 * here.
		 */
		if (*reset_requests != 0)
			return;

		ret = hclge_inform_reset_assert_to_vf(&hdev->vport[vf_id]);
		if (ret)
			dev_err(dev, "inform reset to vf(%u) failed %d!\n",
				hdev->vport->vport_id, ret);
	} else {
		set_bit(HNAE3_FUNC_RESET, reset_requests);
	}
}