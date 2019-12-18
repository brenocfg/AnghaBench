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
struct hclge_dev {TYPE_1__* pdev; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGE_CMD_DATA_NUM ; 
 int HCLGE_CMD_NCL_CONFIG_BD_NUM ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_ncl_config_data_print(struct hclge_dev *hdev,
					struct hclge_desc *desc, int *offset,
					int *length)
{
#define HCLGE_CMD_DATA_NUM		6

	int i;
	int j;

	for (i = 0; i < HCLGE_CMD_NCL_CONFIG_BD_NUM; i++) {
		for (j = 0; j < HCLGE_CMD_DATA_NUM; j++) {
			if (i == 0 && j == 0)
				continue;

			dev_info(&hdev->pdev->dev, "0x%04x | 0x%08x\n",
				 *offset,
				 le32_to_cpu(desc[i].data[j]));
			*offset += sizeof(u32);
			*length -= sizeof(u32);
			if (*length <= 0)
				return;
		}
	}
}