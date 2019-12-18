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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_umv_spc_alc_cmd {int /*<<< orphan*/  space_size; int /*<<< orphan*/  allocate; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_MAC_VLAN_ALLOCATE ; 
 int /*<<< orphan*/  HCLGE_UMV_SPC_ALC_B ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_umv_space(struct hclge_dev *hdev, u16 space_size,
			       u16 *allocated_size, bool is_alloc)
{
	struct hclge_umv_spc_alc_cmd *req;
	struct hclge_desc desc;
	int ret;

	req = (struct hclge_umv_spc_alc_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_ALLOCATE, false);
	if (!is_alloc)
		hnae3_set_bit(req->allocate, HCLGE_UMV_SPC_ALC_B, 1);

	req->space_size = cpu_to_le32(space_size);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"%s umv space failed for cmd_send, ret =%d\n",
			is_alloc ? "allocate" : "free", ret);
		return ret;
	}

	if (is_alloc && allocated_size)
		*allocated_size = le32_to_cpu(desc.data[1]);

	return 0;
}