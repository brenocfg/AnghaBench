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
struct hclge_pkt_buf_alloc {int dummy; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_alloc_tx_buff (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 

__attribute__((used)) static int hclge_tx_buffer_alloc(struct hclge_dev *hdev,
				 struct hclge_pkt_buf_alloc *buf_alloc)
{
	int ret = hclge_cmd_alloc_tx_buff(hdev, buf_alloc);

	if (ret)
		dev_err(&hdev->pdev->dev, "tx buffer alloc failed %d\n", ret);

	return ret;
}