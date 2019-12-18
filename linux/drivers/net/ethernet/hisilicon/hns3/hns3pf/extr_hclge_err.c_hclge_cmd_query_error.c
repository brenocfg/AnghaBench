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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct hclge_dev {int /*<<< orphan*/  hw; TYPE_1__* pdev; } ;
struct hclge_desc {int /*<<< orphan*/  flag; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_cmd_query_error(struct hclge_dev *hdev,
				 struct hclge_desc *desc, u32 cmd, u16 flag)
{
	struct device *dev = &hdev->pdev->dev;
	int desc_num = 1;
	int ret;

	hclge_cmd_setup_basic_desc(&desc[0], cmd, true);
	if (flag) {
		desc[0].flag |= cpu_to_le16(flag);
		hclge_cmd_setup_basic_desc(&desc[1], cmd, true);
		desc_num = 2;
	}

	ret = hclge_cmd_send(&hdev->hw, &desc[0], desc_num);
	if (ret)
		dev_err(dev, "query error cmd failed (%d)\n", ret);

	return ret;
}