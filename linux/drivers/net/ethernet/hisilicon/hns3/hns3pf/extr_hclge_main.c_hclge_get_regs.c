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
struct hnae3_knic_private_info {int dummy; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int fw_version; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_SEPARATE_NUM ; 
 int REG_NUM_REMAIN_MASK ; 
 void* SEPARATOR_VALUE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hclge_fetch_pf_reg (struct hclge_dev*,int*,struct hnae3_knic_private_info*) ; 
 int hclge_get_32_bit_regs (struct hclge_dev*,int,int*) ; 
 int hclge_get_64_bit_regs (struct hclge_dev*,int,int*) ; 
 int hclge_get_dfx_reg (struct hclge_dev*,int*) ; 
 int hclge_get_regs_num (struct hclge_dev*,int*,int*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_regs(struct hnae3_handle *handle, u32 *version,
			   void *data)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u32 regs_num_32_bit, regs_num_64_bit;
	int i, reg_num, separator_num, ret;
	u32 *reg = data;

	*version = hdev->fw_version;

	ret = hclge_get_regs_num(hdev, &regs_num_32_bit, &regs_num_64_bit);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get register number failed, ret = %d.\n", ret);
		return;
	}

	reg += hclge_fetch_pf_reg(hdev, reg, kinfo);

	ret = hclge_get_32_bit_regs(hdev, regs_num_32_bit, reg);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get 32 bit register failed, ret = %d.\n", ret);
		return;
	}
	reg_num = regs_num_32_bit;
	reg += reg_num;
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	for (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	ret = hclge_get_64_bit_regs(hdev, regs_num_64_bit, reg);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Get 64 bit register failed, ret = %d.\n", ret);
		return;
	}
	reg_num = regs_num_64_bit * 2;
	reg += reg_num;
	separator_num = MAX_SEPARATE_NUM - (reg_num & REG_NUM_REMAIN_MASK);
	for (i = 0; i < separator_num; i++)
		*reg++ = SEPARATOR_VALUE;

	ret = hclge_get_dfx_reg(hdev, reg);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Get dfx register failed, ret = %d.\n", ret);
}