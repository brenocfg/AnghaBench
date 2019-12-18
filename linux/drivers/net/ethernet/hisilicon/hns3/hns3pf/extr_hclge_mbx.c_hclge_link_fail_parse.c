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
typedef  int u8 ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HCLGE_LF_REF_CLOCK_LOST 130 
#define  HCLGE_LF_XSFP_ABSENT 129 
#define  HCLGE_LF_XSFP_TX_DISABLE 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void hclge_link_fail_parse(struct hclge_dev *hdev, u8 link_fail_code)
{
	switch (link_fail_code) {
	case HCLGE_LF_REF_CLOCK_LOST:
		dev_warn(&hdev->pdev->dev, "Reference clock lost!\n");
		break;
	case HCLGE_LF_XSFP_TX_DISABLE:
		dev_warn(&hdev->pdev->dev, "SFP tx is disabled!\n");
		break;
	case HCLGE_LF_XSFP_ABSENT:
		dev_warn(&hdev->pdev->dev, "SFP is absent!\n");
		break;
	default:
		break;
	}
}