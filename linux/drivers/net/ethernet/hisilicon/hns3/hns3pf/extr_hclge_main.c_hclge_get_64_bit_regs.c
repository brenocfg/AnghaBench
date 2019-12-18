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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCLGE_64_BIT_DESC_NODATA_LEN ; 
 int HCLGE_64_BIT_REG_RTN_DATANUM ; 
 int /*<<< orphan*/  HCLGE_OPC_QUERY_64_BIT_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 struct hclge_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hclge_desc*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_get_64_bit_regs(struct hclge_dev *hdev, u32 regs_num,
				 void *data)
{
#define HCLGE_64_BIT_REG_RTN_DATANUM 4
#define HCLGE_64_BIT_DESC_NODATA_LEN 1

	struct hclge_desc *desc;
	u64 *reg_val = data;
	__le64 *desc_data;
	int nodata_len;
	int cmd_num;
	int i, k, n;
	int ret;

	if (regs_num == 0)
		return 0;

	nodata_len = HCLGE_64_BIT_DESC_NODATA_LEN;
	cmd_num = DIV_ROUND_UP(regs_num + nodata_len,
			       HCLGE_64_BIT_REG_RTN_DATANUM);
	desc = kcalloc(cmd_num, sizeof(struct hclge_desc), GFP_KERNEL);
	if (!desc)
		return -ENOMEM;

	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_QUERY_64_BIT_REG, true);
	ret = hclge_cmd_send(&hdev->hw, desc, cmd_num);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Query 64 bit register cmd failed, ret = %d.\n", ret);
		kfree(desc);
		return ret;
	}

	for (i = 0; i < cmd_num; i++) {
		if (i == 0) {
			desc_data = (__le64 *)(&desc[i].data[0]);
			n = HCLGE_64_BIT_REG_RTN_DATANUM - nodata_len;
		} else {
			desc_data = (__le64 *)(&desc[i]);
			n = HCLGE_64_BIT_REG_RTN_DATANUM;
		}
		for (k = 0; k < n; k++) {
			*reg_val++ = le64_to_cpu(*desc_data++);

			regs_num--;
			if (!regs_num)
				break;
		}
	}

	kfree(desc);
	return 0;
}