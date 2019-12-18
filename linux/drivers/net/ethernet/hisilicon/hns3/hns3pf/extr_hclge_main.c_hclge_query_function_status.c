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
struct hclge_func_status_cmd {scalar_t__ pf_state; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_QUERY_FUNC_STATUS ; 
 int /*<<< orphan*/  HCLGE_QUERY_MAX_CNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int hclge_parse_func_status (struct hclge_dev*,struct hclge_func_status_cmd*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hclge_query_function_status(struct hclge_dev *hdev)
{
#define HCLGE_QUERY_MAX_CNT	5

	struct hclge_func_status_cmd *req;
	struct hclge_desc desc;
	int timeout = 0;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QUERY_FUNC_STATUS, true);
	req = (struct hclge_func_status_cmd *)desc.data;

	do {
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"query function status failed %d.\n", ret);
			return ret;
		}

		/* Check pf reset is done */
		if (req->pf_state)
			break;
		usleep_range(1000, 2000);
	} while (timeout++ < HCLGE_QUERY_MAX_CNT);

	ret = hclge_parse_func_status(hdev, req);

	return ret;
}