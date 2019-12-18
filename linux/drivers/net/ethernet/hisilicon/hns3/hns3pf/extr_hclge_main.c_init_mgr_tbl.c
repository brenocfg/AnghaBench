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
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_add_mgr_tbl (struct hclge_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hclge_mgr_table ; 

__attribute__((used)) static int init_mgr_tbl(struct hclge_dev *hdev)
{
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(hclge_mgr_table); i++) {
		ret = hclge_add_mgr_tbl(hdev, &hclge_mgr_table[i]);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"add mac ethertype failed, ret =%d.\n",
				ret);
			return ret;
		}
	}

	return 0;
}