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
struct hclge_pf_rst_sync_cmd {scalar_t__ all_vf_ready; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETIME ; 
 int /*<<< orphan*/  HCLGE_OPC_QUERY_VF_RST_RDY ; 
 int /*<<< orphan*/  HCLGE_PF_RESET_SYNC_CNT ; 
 int /*<<< orphan*/  HCLGE_PF_RESET_SYNC_TIME ; 
 int /*<<< orphan*/  HCLGE_RESET_SYNC_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hclge_cmd_reuse_desc (struct hclge_desc*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_func_reset_sync_vf(struct hclge_dev *hdev)
{
	struct hclge_pf_rst_sync_cmd *req;
	struct hclge_desc desc;
	int cnt = 0;
	int ret;

	req = (struct hclge_pf_rst_sync_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_VF_RST_RDY, true);

	do {
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		/* for compatible with old firmware, wait
		 * 100 ms for VF to stop IO
		 */
		if (ret == -EOPNOTSUPP) {
			msleep(HCLGE_RESET_SYNC_TIME);
			return 0;
		} else if (ret) {
			dev_err(&hdev->pdev->dev, "sync with VF fail %d!\n",
				ret);
			return ret;
		} else if (req->all_vf_ready) {
			return 0;
		}
		msleep(HCLGE_PF_RESET_SYNC_TIME);
		hclge_cmd_reuse_desc(&desc, true);
	} while (cnt++ < HCLGE_PF_RESET_SYNC_CNT);

	dev_err(&hdev->pdev->dev, "sync with VF timeout!\n");
	return -ETIME;
}