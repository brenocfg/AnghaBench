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
typedef  int u32 ;
struct hclge_get_m7_bd_cmd {int /*<<< orphan*/  bd_num; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCLGE_OPC_M7_STATS_BD ; 
 int /*<<< orphan*/  HCLGE_OPC_M7_STATS_INFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int hclge_dbg_cmd_send (struct hclge_dev*,struct hclge_desc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hclge_desc*) ; 
 struct hclge_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_dbg_get_m7_stats_info(struct hclge_dev *hdev)
{
	struct hclge_desc *desc_src, *desc_tmp;
	struct hclge_get_m7_bd_cmd *req;
	struct hclge_desc desc;
	u32 bd_num, buf_len;
	int ret, i;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_M7_STATS_BD, true);

	req = (struct hclge_get_m7_bd_cmd *)desc.data;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"get firmware statistics bd number failed, ret = %d\n",
			ret);
		return;
	}

	bd_num = le32_to_cpu(req->bd_num);

	buf_len	 = sizeof(struct hclge_desc) * bd_num;
	desc_src = kzalloc(buf_len, GFP_KERNEL);
	if (!desc_src) {
		dev_err(&hdev->pdev->dev,
			"allocate desc for get_m7_stats failed\n");
		return;
	}

	desc_tmp = desc_src;
	ret  = hclge_dbg_cmd_send(hdev, desc_tmp, 0, bd_num,
				  HCLGE_OPC_M7_STATS_INFO);
	if (ret) {
		kfree(desc_src);
		dev_err(&hdev->pdev->dev,
			"get firmware statistics failed, ret = %d\n", ret);
		return;
	}

	for (i = 0; i < bd_num; i++) {
		dev_info(&hdev->pdev->dev, "0x%08x  0x%08x  0x%08x\n",
			 le32_to_cpu(desc_tmp->data[0]),
			 le32_to_cpu(desc_tmp->data[1]),
			 le32_to_cpu(desc_tmp->data[2]));
		dev_info(&hdev->pdev->dev, "0x%08x  0x%08x  0x%08x\n",
			 le32_to_cpu(desc_tmp->data[3]),
			 le32_to_cpu(desc_tmp->data[4]),
			 le32_to_cpu(desc_tmp->data[5]));

		desc_tmp++;
	}

	kfree(desc_src);
}