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
struct hclge_dev {int /*<<< orphan*/  hw; TYPE_1__* pdev; } ;
struct hclge_desc {void** data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int revision; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CONFIG_ROCEE_RAS_INT_EN ; 
 int /*<<< orphan*/  HCLGE_ROCEE_RAS_CE_INT_EN ; 
 int /*<<< orphan*/  HCLGE_ROCEE_RAS_CE_INT_EN_MASK ; 
 int /*<<< orphan*/  HCLGE_ROCEE_RAS_NFE_INT_EN ; 
 int /*<<< orphan*/  HCLGE_ROCEE_RAS_NFE_INT_EN_MASK ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_log_and_clear_rocee_ras_error (struct hclge_dev*) ; 
 int /*<<< orphan*/  hnae3_dev_roce_supported (struct hclge_dev*) ; 

int hclge_config_rocee_ras_interrupt(struct hclge_dev *hdev, bool en)
{
	struct device *dev = &hdev->pdev->dev;
	struct hclge_desc desc;
	int ret;

	if (hdev->pdev->revision < 0x21 || !hnae3_dev_roce_supported(hdev))
		return 0;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_CONFIG_ROCEE_RAS_INT_EN, false);
	if (en) {
		/* enable ROCEE hw error interrupts */
		desc.data[0] = cpu_to_le32(HCLGE_ROCEE_RAS_NFE_INT_EN);
		desc.data[1] = cpu_to_le32(HCLGE_ROCEE_RAS_CE_INT_EN);

		hclge_log_and_clear_rocee_ras_error(hdev);
	}
	desc.data[2] = cpu_to_le32(HCLGE_ROCEE_RAS_NFE_INT_EN_MASK);
	desc.data[3] = cpu_to_le32(HCLGE_ROCEE_RAS_CE_INT_EN_MASK);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(dev, "failed(%d) to config ROCEE RAS interrupt\n", ret);

	return ret;
}