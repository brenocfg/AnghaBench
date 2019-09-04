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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_query_function_status (struct hclge_dev*) ; 
 int hclge_query_pf_resource (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_get_cap(struct hclge_dev *hdev)
{
	int ret;

	ret = hclge_query_function_status(hdev);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"query function status error %d.\n", ret);
		return ret;
	}

	/* get pf resource */
	ret = hclge_query_pf_resource(hdev);
	if (ret)
		dev_err(&hdev->pdev->dev, "query pf resource error %d.\n", ret);

	return ret;
}