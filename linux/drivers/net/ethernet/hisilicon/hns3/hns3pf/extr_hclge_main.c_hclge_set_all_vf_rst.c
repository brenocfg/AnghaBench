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
struct hclge_vport {int /*<<< orphan*/  vport_id; int /*<<< orphan*/  state; } ;
struct hclge_dev {int num_vmdq_vport; int num_alloc_vport; TYPE_1__* pdev; struct hclge_vport* vport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_VPORT_STATE_ALIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int hclge_inform_reset_assert_to_vf (struct hclge_vport*) ; 
 int hclge_set_vf_rst (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_set_all_vf_rst(struct hclge_dev *hdev, bool reset)
{
	int i;

	for (i = hdev->num_vmdq_vport + 1; i < hdev->num_alloc_vport; i++) {
		struct hclge_vport *vport = &hdev->vport[i];
		int ret;

		/* Send cmd to set/clear VF's FUNC_RST_ING */
		ret = hclge_set_vf_rst(hdev, vport->vport_id, reset);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"set vf(%d) rst failed %d!\n",
				vport->vport_id, ret);
			return ret;
		}

		if (!reset || !test_bit(HCLGE_VPORT_STATE_ALIVE, &vport->state))
			continue;

		/* Inform VF to process the reset.
		 * hclge_inform_reset_assert_to_vf may fail if VF
		 * driver is not loaded.
		 */
		ret = hclge_inform_reset_assert_to_vf(vport);
		if (ret)
			dev_warn(&hdev->pdev->dev,
				 "inform reset to vf(%d) failed %d!\n",
				 vport->vport_id, ret);
	}

	return 0;
}