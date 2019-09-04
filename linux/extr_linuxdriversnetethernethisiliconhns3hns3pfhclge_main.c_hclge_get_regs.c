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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int fw_version; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_get_32_bit_regs (struct hclge_dev*,int,void*) ; 
 int hclge_get_64_bit_regs (struct hclge_dev*,int,void*) ; 
 int hclge_get_regs_num (struct hclge_dev*,int*,int*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_regs(struct hnae3_handle *handle, u32 *version,
			   void *data)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u32 regs_num_32_bit, regs_num_64_bit;
	int ret;

	*version = hdev->fw_version;

	ret = hclge_get_regs_num(hdev, &regs_num_32_bit, &regs_num_64_bit);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get register number failed, ret = %d.\n", ret);
		return;
	}

	ret = hclge_get_32_bit_regs(hdev, regs_num_32_bit, data);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get 32 bit register failed, ret = %d.\n", ret);
		return;
	}

	data = (u32 *)data + regs_num_32_bit;
	ret = hclge_get_64_bit_regs(hdev, regs_num_64_bit,
				    data);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Get 64 bit register failed, ret = %d.\n", ret);
}